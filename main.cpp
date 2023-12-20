#include <QApplication>
#include <QMainWindow>
#include <QUndoStack>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QStringListModel>
#include <QListView>
#include <QDockWidget>
#include <QUndoView>

#include "insertcommand.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringListModel* mListModel = new QStringListModel();
    QStringList aStrings;
    for (int i = 0; i < 10; ++i)
    {
        aStrings << "test string for undo/redo " + QString::number(i);
    }
    mListModel->setStringList(aStrings);
    // QStringListModel* mListModel = new QStringListModel(aStrings);

    QListView *mListView = new QListView();
    mListView->setModel(mListModel);


    // 创建主窗口
    QMainWindow mainWindow;

    // 创建撤销栈
    QUndoStack *undoStack = new QUndoStack();

    // 创建撤销和重做按钮
    QPushButton undoButton("Undo");
    QPushButton redoButton("Redo");
    QPushButton executeButton("Excute");

    // auto currentCommandLabel = new QLabel();

    // 连接撤销按钮的点击事件到撤销栈的undo()槽函数
    QObject::connect(&undoButton, &QPushButton::clicked, undoStack,[&]() {
         // qDebug() << "last undo: " << undoStack.undoText();
        undoStack->undo();
         // currentCommandLabel->setText(undoStack.command);
        // qDebug() << "next undo: " << undoStack.undoText();
    });

    // 连接重做按钮的点击事件到撤销栈的redo()槽函数
    QObject::connect(&redoButton, &QPushButton::clicked, undoStack,[&]() {
        // qDebug() << "last redo: " << undoStack.redoText();
        undoStack->redo();
        // currentCommandLabel->setText(undoStack.command(-1)->text());
        // qDebug() << "next redo: " << undoStack.redoText();
    });

    // QDockWidget *undoDockWidget = new QDockWidget;
    // undoDockWidget->setWindowTitle("Command List");
    // undoDockWidget->setWidget(new QUndoView(undoStack));
    // addDockWidget(Qt::RightDockWidgetArea, undoDockWidget);

    QUndoView * undoView= new QUndoView(undoStack);

    // 创建布局并添加按钮
    QVBoxLayout layout;
    layout.addWidget(&undoButton);
    layout.addWidget(&redoButton);
    layout.addWidget(&executeButton);
    // layout.addWidget(currentCommandLabel);
    layout.addWidget(mListView);
    layout.addWidget(undoView);

    // QString commandText = undoStack->text(0);
    // layout.addWidget(new QLabel(commandText));

    // 创建中心窗口部件并设置布局
    QWidget centralWidget;
    centralWidget.setLayout(&layout);

    // 将中心窗口部件设置为主窗口的中心部件
    mainWindow.setCentralWidget(&centralWidget);

    QObject::connect(&executeButton, &QPushButton::clicked, undoStack, [&]() {
        QModelIndex aIndex = mListView->currentIndex();
        MyUndoCommand* newCommand = new MyUndoCommand(aIndex, mListModel);
        undoStack->push(newCommand);
    });
    // int commandCount = 1;
    // QObject::connect(&executeButton, &QPushButton::clicked, &undoStack, [&]() {
    //     QString commandText = "Command " + QString::number(commandCount++);
    //     qDebug() << "Command: " << commandText;
    //     MyUndoCommand* newCommand = new MyUndoCommand(commandText);
    //     undoStack.push(newCommand);
    //     // currentCommandLabel->setText(commandText);
    // });

    // 显示主窗口
    mainWindow.show();

    return app.exec();
}
