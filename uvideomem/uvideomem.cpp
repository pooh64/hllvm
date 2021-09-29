#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QtWidgets/QApplication>

#include "uvideomem.h"

struct VideoMem {
	uint32_t *mem;
	uint32_t max_x;
	uint32_t max_y;

	VideoMem(uint32_t max_x_, uint32_t max_y_)
	{
		max_x = max_x_;
		max_y = max_y_;
		mem = new uint32_t[max_x_ * max_y];
	}

	~VideoMem()
	{
		delete[] mem;
	}
};

struct VideoMemManager : public QObject {
	Q_OBJECT
public:
	VideoMemManager(VideoMem &vmem)
	{
		qimg = QImage((uchar *)vmem.mem, vmem.max_x, vmem.max_y, QImage::Format_RGBX8888);
		connect(&timer, SIGNAL(timeout()), this, SLOT(Redraw()));
		timer.start(1000 / 60);
	}
	virtual ~VideoMemManager() {}

public slots:
	void Redraw()
	{
		ql.setPixmap(QPixmap::fromImage(qimg));
		ql.show();
	}

private:
	QImage qimg;
	QLabel ql;
	QTimer timer;
};

uint32_t volatile *uvideomem;

extern "C" void uvideomem_init(void (*fn)())
{
	char render_name[] = "uvideomem_screen";
	char *argv[] = {render_name, nullptr};
	int argc = 1;
	QApplication a(argc, argv);

	VideoMem vmem(UVIDEOMEM_W, UVIDEOMEM_H);
	uvideomem = vmem.mem;
	auto manager = VideoMemManager(vmem);
	auto t = QThread::create(fn);
	t->start();
	exit(a.exec());
}

#include "uvideomem.moc"