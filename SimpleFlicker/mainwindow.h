#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "catalog.h"
#include "itemmodel.h"

#include <QAbstractItemModelTester>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void requestItems(int num, int sleepMs);
private:
    Ui::MainWindow *ui;
    QThread* catalogThread;
    Catalog* catalog;

    ItemModel* itemModel;
    QAbstractItemModelTester* tester;
};
#endif // MAINWINDOW_H
