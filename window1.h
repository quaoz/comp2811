#ifndef WINDOW1_H
#define WINDOW1_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class Window1 : public QWidget {
    Q_OBJECT
public:
    explicit Window1(QWidget* parent = nullptr);
};

#endif // WINDOW1_H
