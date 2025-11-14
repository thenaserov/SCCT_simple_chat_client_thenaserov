#include "scct.h"
#include "ui_scct.h"

SCCT::SCCT(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SCCT)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(ui->connectButton, &QPushButton::clicked,
            this, &SCCT::connectToServer);

    connect(ui->sendButton, &QPushButton::clicked,
            this, &SCCT::sendMessage);

    connect(socket, &QTcpSocket::readyRead,
            this, &SCCT::onReadyRead);

    connect(socket, &QTcpSocket::connected, [this]() {
        ui->chatView->appendPlainText("Connected to server!");
    });

    connect(socket, &QTcpSocket::disconnected, [this]() {
        ui->chatView->appendPlainText("Disconnected from server");
    });
}

SCCT::~SCCT()
{
    delete ui;
}

void SCCT::connectToServer()
{
    QString host = ui->serverLineEdit->text();
    int port = ui->portLineEdit->text().toInt();

    socket->connectToHost(host, port);

    ui->chatView->appendPlainText("Connecting...");
}

void SCCT::sendMessage()
{
    QString msg = ui->messageLineEdit->text().trimmed();
    if(msg.isEmpty()) return;

    socket->write(msg.toUtf8() + '\n');
    ui->chatView->appendPlainText(ui->usernameLineEdit->text() + " : " + ui->messageLineEdit->text() + "\n");
    ui->messageLineEdit->clear();
}

void SCCT::onReadyRead()
{
    while(socket->canReadLine()) {
        QString line = socket->readLine().trimmed();
        ui->chatView->appendPlainText(line);
    }
}

void SCCT::on_messageLineEdit_returnPressed()
{
    sendMessage();
}
