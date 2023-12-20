#include "insertcommand.h"
#include <QUndoCommand>
#include <QDebug>

MyUndoCommand :: MyUndoCommand(QModelIndex& index, QStringListModel *model) :
    QUndoCommand(("Insert ") + QString::number(index.row())),
    mIndex(index),
    mModel(model)
{}

MyUndoCommand::~MyUndoCommand() = default;

void MyUndoCommand::undo()
    {
        mModel->removeRows(mIndex.row(), 1);
    }

void MyUndoCommand::redo()
    {
        mModel->insertRows(mIndex.row(), 1);
        mModel->setData(mIndex, QString("Insert string " + QString::number(mIndex.row())));
    }


