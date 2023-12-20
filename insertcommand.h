#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoCommand>
#include <QStringListModel>

class MyUndoCommand : public QUndoCommand
{
public:
    MyUndoCommand(QModelIndex& index, QStringListModel *model);
    ~MyUndoCommand() override;

    void undo() override;


    void redo() override;

private:
    QModelIndex mIndex;
    QStringListModel *mModel;

};
#endif // MAINWINDOW_H
