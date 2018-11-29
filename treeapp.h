#ifndef TREEAPP_H
#define TREEAPP_H

#include <QDialog>
#include <QTreeWidget>
#include <QString>

namespace Ui {
class TreeApp;
}

class TreeApp : public QDialog
{
    Q_OBJECT

public:
    explicit TreeApp(QWidget *parent = nullptr);
    ~TreeApp();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

private:
    Ui::TreeApp *ui;

    QTreeWidgetItem * addTreeRoot();
    void addTreeChild(QTreeWidgetItem *parent);

};

#endif // TREEAPP_H
