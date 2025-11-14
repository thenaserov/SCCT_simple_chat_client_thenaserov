#ifndef SCCT_H
#define SCCT_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class SCCT; }
QT_END_NAMESPACE

class SCCT : public QMainWindow
{
    Q_OBJECT

public:
    explicit SCCT(QWidget *parent = nullptr);
    ~SCCT();

private slots:
    void connectToServer();
    void sendMessage();
    void onReadyRead();

    void on_messageLineEdit_returnPressed();

private:
    Ui::SCCT *ui;
    QTcpSocket *socket;
};

#endif // SCCT_H
