#include "calcultor.h"
#include "ui_calcultor.h"
#include <QDebug>

calcultor::calcultor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::calcultor),
    _nowmode(_mode::_64bit),_nowsympol(_sympol::none),
    _integer(true),_lastvalue(0),_acaftersympol(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::SubWindow);
    ui->cb_mode->setCurrentText("64 BIT");
    this->on_pb_AC_clicked();
    this->on_pb_dec_clicked();
//    ui->cb_mode->setEnabled(false);

}

calcultor::~calcultor()
{
    delete ui;
}

void calcultor::on_cb_mode_currentIndexChanged(int index)
{
    switch (index) {
    case _mode::_8bit:
    {
        bool ok;
        int32_t res = ui->le_hex->text().toInt(&ok,16);
        int8_t xxx = static_cast<int8_t>(res);
        setres(xxx);
    }
        break;
    case _mode::_8bitu:
    {
        bool ok;
        uint32_t xxx = ui->le_hex->text().toUInt(&ok,16);
        uint8_t res = static_cast<uint8_t>(xxx);
        setres(res);
    }
        break;
    case _mode::_16bit:
    {
        bool ok;
        int32_t xxx = ui->le_hex->text().toInt(&ok,16);
        int16_t res = static_cast<int16_t>(xxx);
        setres(res);
    }
        break;
    case _mode::_16bitu:
    {
        bool ok;
        uint32_t xxx = ui->le_hex->text().toUInt(&ok,16);
        uint16_t res = static_cast<uint16_t>(xxx);
        setres(res);
    }
        break;
    case _mode::_32bit:
    {
        bool ok;
        int32_t res = ui->le_hex->text().toInt(&ok,16);
        setres(res);
    }
        break;
    case _mode::_32bitu:
    {
        bool ok;
        uint32_t res = ui->le_hex->text().toUInt(&ok,16);
        setres(res);
    }
        break;
    case _mode::_64bit:
    {
        bool ok;
        int64_t res = ui->le_hex->text().toLongLong(&ok,16);
        setres(res);
    }
        break;
    case _mode::_64bitu:
    {
        bool ok;
        uint64_t res = ui->le_hex->text().toULongLong(&ok,16);
        setres(res);
    }
        break;
    default:
        break;
    }
    _nowmode = index;
}

void calcultor::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        _integer = true;
        ui->scrollArea->setVisible(true);
        ui->scrollAreaWidgetContents->setVisible(true);
        break;
    case 1:
        _integer = false;
        ui->scrollArea->setHidden(true);
        ui->scrollAreaWidgetContents->setHidden(true);
        break;
    default:
        break;
    }
    _nowsympol = _sympol::none;
}

void calcultor::on_pb_AC_clicked()
{
    ui->le_bin->setText(QString::number(0));
    ui->le_dec->setText(QString::number(0));
    ui->le_oct->setText(QString::number(0));
    ui->le_hex->setText(QString::number(0));
}

void calcultor::on_pb_hex_clicked()
{
    if (_nowtype == _type::_hex)
        return;
    _nowtype = _type::_hex;
    ui->pb_2->setEnabled(true);ui->pb_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_3->setEnabled(true);ui->pb_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_4->setEnabled(true);ui->pb_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_5->setEnabled(true);ui->pb_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_6->setEnabled(true);ui->pb_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_7->setEnabled(true);ui->pb_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_8->setEnabled(true);ui->pb_8->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_9->setEnabled(true);ui->pb_9->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_A->setEnabled(true);ui->pb_A->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_B->setEnabled(true);ui->pb_B->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_C->setEnabled(true);ui->pb_C->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_D->setEnabled(true);ui->pb_D->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_E->setEnabled(true);ui->pb_E->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_F->setEnabled(true);ui->pb_F->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_hex->setStyleSheet("background-color: rgb(0, 197, 0);");
    ui->pb_dec->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_oct->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_bin->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->le_hex->setReadOnly(false);ui->le_hex->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->le_dec->setReadOnly(true);ui->le_dec->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_oct->setReadOnly(true);ui->le_oct->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_bin->setReadOnly(true);ui->le_bin->setStyleSheet("background-color: rgb(162, 162, 162);");
}

void calcultor::on_pb_dec_clicked()
{
    if (_nowtype == _type::_dec)
        return;
    _nowtype = _type::_dec;
    ui->pb_2->setEnabled(true);ui->pb_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_3->setEnabled(true);ui->pb_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_4->setEnabled(true);ui->pb_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_5->setEnabled(true);ui->pb_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_6->setEnabled(true);ui->pb_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_7->setEnabled(true);ui->pb_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_8->setEnabled(true);ui->pb_8->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_9->setEnabled(true);ui->pb_9->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_A->setEnabled(false);ui->pb_A->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_B->setEnabled(false);ui->pb_B->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_C->setEnabled(false);ui->pb_C->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_D->setEnabled(false);ui->pb_D->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_E->setEnabled(false);ui->pb_E->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_F->setEnabled(false);ui->pb_F->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_hex->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_dec->setStyleSheet("background-color: rgb(0, 197, 0);");
    ui->pb_oct->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_bin->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->le_hex->setReadOnly(true);ui->le_hex->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_dec->setReadOnly(false);ui->le_dec->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->le_oct->setReadOnly(true);ui->le_oct->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_bin->setReadOnly(true);ui->le_bin->setStyleSheet("background-color: rgb(162, 162, 162);");
}

void calcultor::on_pb_oct_clicked()
{
    if (_nowtype == _type::_oct)
        return;
    _nowtype = _type::_oct;
    ui->pb_2->setEnabled(true);ui->pb_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_3->setEnabled(true);ui->pb_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_4->setEnabled(true);ui->pb_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_5->setEnabled(true);ui->pb_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_6->setEnabled(true);ui->pb_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_7->setEnabled(true);ui->pb_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pb_8->setEnabled(false);ui->pb_8->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_9->setEnabled(false);ui->pb_9->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_A->setEnabled(false);ui->pb_A->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_B->setEnabled(false);ui->pb_B->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_C->setEnabled(false);ui->pb_C->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_D->setEnabled(false);ui->pb_D->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_E->setEnabled(false);ui->pb_E->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_F->setEnabled(false);ui->pb_F->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_hex->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_dec->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_oct->setStyleSheet("background-color: rgb(0, 197, 0);");
    ui->pb_bin->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->le_hex->setReadOnly(true);ui->le_hex->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_dec->setReadOnly(true);ui->le_dec->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_oct->setReadOnly(false);ui->le_oct->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->le_bin->setReadOnly(true);ui->le_bin->setStyleSheet("background-color: rgb(162, 162, 162);");
}

void calcultor::on_pb_bin_clicked()
{
    if (_nowtype == _type::_bin)
        return;
    _nowtype = _type::_bin;
    ui->pb_2->setEnabled(false);ui->pb_2->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_3->setEnabled(false);ui->pb_3->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_4->setEnabled(false);ui->pb_4->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_5->setEnabled(false);ui->pb_5->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_6->setEnabled(false);ui->pb_6->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_7->setEnabled(false);ui->pb_7->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_8->setEnabled(false);ui->pb_8->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_9->setEnabled(false);ui->pb_9->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_A->setEnabled(false);ui->pb_A->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_B->setEnabled(false);ui->pb_B->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_C->setEnabled(false);ui->pb_C->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_D->setEnabled(false);ui->pb_D->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_E->setEnabled(false);ui->pb_E->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_F->setEnabled(false);ui->pb_F->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->pb_hex->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_dec->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_oct->setStyleSheet("background-color: rgb(0, 85, 255);");
    ui->pb_bin->setStyleSheet("background-color: rgb(0, 197, 0);");
    ui->le_hex->setReadOnly(true);ui->le_hex->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_dec->setReadOnly(true);ui->le_dec->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_oct->setReadOnly(true);ui->le_oct->setStyleSheet("background-color: rgb(162, 162, 162);");
    ui->le_bin->setReadOnly(false);ui->le_bin->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void calcultor::on_pb_0_clicked()
{
    addstr("0");
}

void calcultor::on_pb_1_clicked()
{
    addstr("1");
}

void calcultor::on_pb_2_clicked()
{
    addstr("2");
}

void calcultor::on_pb_3_clicked()
{
    addstr("3");
}

void calcultor::on_pb_4_clicked()
{
    addstr("4");
}

void calcultor::on_pb_5_clicked()
{
    addstr("5");
}

void calcultor::on_pb_6_clicked()
{
    addstr("6");
}

void calcultor::on_pb_7_clicked()
{
    addstr("7");
}

void calcultor::on_pb_8_clicked()
{
    addstr("8");
}

void calcultor::on_pb_9_clicked()
{
    addstr("9");
}

void calcultor::on_pb_A_clicked()
{
    addstr("A");
}

void calcultor::on_pb_B_clicked()
{
    addstr("B");
}

void calcultor::on_pb_C_clicked()
{
    addstr("C");
}

void calcultor::on_pb_D_clicked()
{
    addstr("D");
}

void calcultor::on_pb_E_clicked()
{
    addstr("E");
}

void calcultor::on_pb_F_clicked()
{
    addstr("F");
}

void calcultor::addstr(const QString &key)
{
    if (_acaftersympol)
    {
        this->on_pb_AC_clicked();
        _acaftersympol = false;
    }
//    if (ui->cb_mode->currentText() == "64 BIT U")
//    {
//        uint64_t newdecvalue = 0;
//        QString strhexvalue = "";
//        bool ok;
//        switch (_nowtype) {
//        case _type::_hex:
//        {
//            strhexvalue = ui->le_hex->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toULongLong(&ok,16);
//        }
//            break;
//        case _type::_dec:
//        {
//            QString strhexvalue = ui->le_dec->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toULongLong(&ok,10);
//        }
//            break;
//        case _type::_oct:
//        {
//            QString strhexvalue = ui->le_oct->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toULongLong(&ok,8);
//        }
//            break;
//        case _type::_bin:
//        {
//            QString strhexvalue = ui->le_bin->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toULongLong(&ok,2);
//        }
//            break;
//        default:
//            break;
//        }
//        if(ok){
//    //        ui->le_hex->setText(QString::number(newdecvalue,16));
//    //        ui->le_dec->setText(QString::number(newdecvalue,10));
//    //        ui->le_oct->setText(QString::number(newdecvalue,8));
//    //        ui->le_bin->setText(QString::number(newdecvalue,2));
//            setres(newdecvalue);
//        }
//    }
//    else
//    {
//        int64_t newdecvalue = 0;
//        QString strhexvalue = "";
//        bool ok;
//        switch (_nowtype) {
//        case _type::_hex:
//        {
//            strhexvalue = ui->le_hex->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toLongLong(&ok,16);
//        }
//            break;
//        case _type::_dec:
//        {
//            QString strhexvalue = ui->le_dec->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toLongLong(&ok,10);
//        }
//            break;
//        case _type::_oct:
//        {
//            QString strhexvalue = ui->le_oct->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toLongLong(&ok,8);
//        }
//            break;
//        case _type::_bin:
//        {
//            QString strhexvalue = ui->le_bin->text();
//            strhexvalue += key;
//            newdecvalue = strhexvalue.toLongLong(&ok,2);
//        }
//            break;
//        default:
//            break;
//        }
//        if(ok){
//    //        ui->le_hex->setText(QString::number(newdecvalue,16));
//    //        ui->le_dec->setText(QString::number(newdecvalue,10));
//    //        ui->le_oct->setText(QString::number(newdecvalue,8));
//    //        ui->le_bin->setText(QString::number(newdecvalue,2));
//            setres(newdecvalue);
//        }
//    }
    bool ok;
    switch (_nowmode) {
    case _mode::_8bit:
    {
        int16_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<2)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,10);
            if ( newdecvalue > 127 || newdecvalue < -128 )
                ok = false;
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,8);
            if ( newdecvalue > 127 || newdecvalue < -128 )
                ok = false;
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<8)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_8bitu:
    {
        uint16_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<2)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,10);
            if(newdecvalue > 255 || newdecvalue < 0)
                ok = false;
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,8);
            if(newdecvalue > 255 || newdecvalue < 0)
                ok = false;
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<8)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_16bit:
    {
        int16_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<4)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toShort(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toShort(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<16)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_16bitu:
    {
        uint16_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<4)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toUShort(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toUShort(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<16)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_32bit:
    {
        int32_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<8)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toInt(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toInt(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<32)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_32bitu:
    {
        uint32_t newdecvalue = 0;
        QString strhexvalue = "";
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            if(strhexvalue.length()<8)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toUInt(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toUInt(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            if(strhexvalue.length()<32)
                strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_64bit:
    {
        int64_t newdecvalue = 0;
        QString strhexvalue = "";
        bool ok;
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    case _mode::_64bitu:
    {
        uint64_t newdecvalue = 0;
        QString strhexvalue = "";
        bool ok;
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toULongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toULongLong(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toULongLong(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            strhexvalue += key;
            newdecvalue = strhexvalue.toULongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
            setres(newdecvalue);
        }
    }
        break;
    default:
        break;
    }
}

void calcultor::setres(int8_t res)
{
    ui->le_hex->setText(QString::number(res,16).right(2));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8).right(3));
    ui->le_bin->setText(QString::number(res,2).right(8));
}

void calcultor::setres(uint8_t res)
{
    ui->le_hex->setText(QString::number(res,16).right(2));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8).right(3));
    ui->le_bin->setText(QString::number(res,2).right(8));
}

void calcultor::setres(int16_t res)
{
    ui->le_hex->setText(QString::number(res,16).right(4));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8).right(6));
    ui->le_bin->setText(QString::number(res,2).right(16));
}

void calcultor::setres(uint16_t res)
{
    ui->le_hex->setText(QString::number(res,16).right(4));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8).right(6));
    ui->le_bin->setText(QString::number(res,2).right(16));

}

void calcultor::setres(int32_t res)
{
    ui->le_hex->setText(QString::number(res,16));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8));
    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::setres(uint32_t res)
{
    ui->le_hex->setText(QString::number(res,16));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8));
    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::setres(int64_t res)
{
    ui->le_hex->setText(QString::number(res,16));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8));
    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::setres(uint64_t res)
{
    ui->le_hex->setText(QString::number(res,16));
    ui->le_dec->setText(QString::number(res,10));
    ui->le_oct->setText(QString::number(res,8));
    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_and_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::andd;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::andd;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_or_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::orr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::orr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_not_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = ~nowvalue;
        setres(res);
    }
    else
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = ~nowvalue;
        setres(res);
    }
//    ui->le_hex->setText(QString::number(res,16));
//    ui->le_dec->setText(QString::number(res,10));
//    ui->le_oct->setText(QString::number(res,8));
//    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_xor_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::xorr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::xorr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_inc_clicked()
{
//    this->_nowsympol = _sympol::incc;
//    bool ok;
//    QString strhexvalue = ui->le_dec->text();
//    this->_lastvalue = strhexvalue.toLong(&ok,10);
//    _acaftersympol = true;
    switch (_nowmode) {
    case _mode::_8bit:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int8_t res = static_cast<int8_t>(nowvalue);
        res++;
        setres(res);
    }
        break;
    case _mode::_8bitu:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        uint8_t res = static_cast<uint8_t>(nowvalue);
        res++;
        setres(res);
    }
        break;
    case _mode::_16bit:
    {
        bool ok;
        int16_t nowvalue = ui->le_dec->text().toShort(&ok,10);
        int16_t res = nowvalue + 1;
        setres(res);
    }
        break;
    case _mode::_16bitu:
    {
        bool ok;
        uint16_t nowvalue = ui->le_dec->text().toUShort(&ok,10);
        uint16_t res = nowvalue + 1;
        setres(res);
    }
        break;
    case _mode::_32bit:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toInt(&ok,10);
        int32_t res = nowvalue + 1;
        setres(res);
    }
        break;
    case _mode::_32bitu:
    {
        bool ok;
        uint32_t nowvalue = ui->le_dec->text().toUInt(&ok,10);
        uint32_t res = nowvalue + 1;
        setres(res);
    }
        break;
    case _mode::_64bit:
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = nowvalue + 1;
        setres(res);
    }
        break;
    case _mode::_64bitu:
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = nowvalue + 1;
        setres(res);
    }
        break;
    default:
        break;
    }
//    ui->le_hex->setText(QString::number(res,16));
//    ui->le_dec->setText(QString::number(res,10));
//    ui->le_oct->setText(QString::number(res,8));
//    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_decc_clicked()
{
//    this->_nowsympol = _sympol::decc;
//    bool ok;
//    QString strhexvalue = ui->le_dec->text();
//    this->_lastvalue = strhexvalue.toLong(&ok,10);
//    _acaftersympol = true;
    switch (_nowmode) {
    case _mode::_8bit:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toInt(&ok,10);
        int8_t res = static_cast<int8_t>(nowvalue);
        res--;
        setres(res);
    }
        break;
    case _mode::_8bitu:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toInt(&ok,10);
        uint8_t res = static_cast<uint8_t>(nowvalue);
        res--;
        setres(res);
    }
        break;
    case _mode::_16bit:
    {
        bool ok;
        int16_t nowvalue = ui->le_dec->text().toShort(&ok,10);
        int16_t res = nowvalue - 1;
        setres(res);
    }
        break;
    case _mode::_16bitu:
    {
        bool ok;
        uint16_t nowvalue = ui->le_dec->text().toUShort(&ok,10);
        uint16_t res = nowvalue - 1;
        setres(res);
    }
        break;
    case _mode::_32bit:
    {
        bool ok;
        int32_t nowvalue = ui->le_dec->text().toInt(&ok,10);
        int32_t res = nowvalue - 1;
        setres(res);
    }
        break;
    case _mode::_32bitu:
    {
        bool ok;
        uint32_t nowvalue = ui->le_dec->text().toUInt(&ok,10);
        uint32_t res = nowvalue - 1;
        setres(res);
    }
        break;
    case _mode::_64bit:
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = nowvalue - 1;
        setres(res);
    }
        break;
    case _mode::_64bitu:
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = nowvalue - 1;
        setres(res);
    }
        break;
    default:
        break;
    }
//    if (ui->cb_mode->currentText() == "64 BIT U")
//    {
//        bool ok;
//        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
//        uint64_t res = nowvalue - 1;
//        setres(res);
//    }
//    else
//    {
//        bool ok;
//        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
//        int64_t res = nowvalue - 1;
//        setres(res);
//    }
//    ui->le_hex->setText(QString::number(res,16));
//    ui->le_dec->setText(QString::number(res,10));
//    ui->le_oct->setText(QString::number(res,8));
//    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_shl_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::shll;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::shll;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_shr_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::shrr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::shrr;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_rol_clicked()
{
//    this->_nowsympol = _sympol::roll;
//    bool ok;
//    QString strhexvalue = ui->le_dec->text();
//    this->_lastvalue = strhexvalue.toLong(&ok,10);
//    _acaftersympol = true;
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = (nowvalue << 2) | (nowvalue >> (sizeof(nowvalue)*8 - 2));
        setres(res);
    }
    else
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = (nowvalue << 2) | (nowvalue >> (sizeof(nowvalue)*8 - 2));
        setres(res);
    }
//    ui->le_hex->setText(QString::number(res,16));
//    ui->le_dec->setText(QString::number(res,10));
//    ui->le_oct->setText(QString::number(res,8));
//    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_ror_clicked()
{
//    this->_nowsympol = _sympol::rorr;
//    bool ok;
//    QString strhexvalue = ui->le_dec->text();
//    this->_lastvalue = strhexvalue.toLong(&ok,10);
//    _acaftersympol = true;
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = (nowvalue << 2) | (nowvalue >> (sizeof(nowvalue)*8 - 2));
        setres(res);
    }
    else
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = (nowvalue << 2) | (nowvalue >> (sizeof(nowvalue)*8 - 2));
        setres(res);
    }
//    ui->le_hex->setText(QString::number(res,16));
//    ui->le_dec->setText(QString::number(res,10));
//    ui->le_oct->setText(QString::number(res,8));
//    ui->le_bin->setText(QString::number(res,2));
}

void calcultor::on_pb_delete_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        uint64_t newdecvalue = 0;
        QString strhexvalue = "";
        bool ok;
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toULongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toULongLong(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toULongLong(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toULongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
    //        ui->le_hex->setText(QString::number(newdecvalue,16));
    //        ui->le_dec->setText(QString::number(newdecvalue,10));
    //        ui->le_oct->setText(QString::number(newdecvalue,8));
    //        ui->le_bin->setText(QString::number(newdecvalue,2));
            setres(newdecvalue);
        }
    }
    else
    {
        int64_t newdecvalue = 0;
        QString strhexvalue = "";
        bool ok;
        switch (_nowtype) {
        case _type::_hex:
        {
            strhexvalue = ui->le_hex->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toLongLong(&ok,16);
        }
            break;
        case _type::_dec:
        {
            QString strhexvalue = ui->le_dec->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toLongLong(&ok,10);
        }
            break;
        case _type::_oct:
        {
            QString strhexvalue = ui->le_oct->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toLongLong(&ok,8);
        }
            break;
        case _type::_bin:
        {
            QString strhexvalue = ui->le_bin->text();
            strhexvalue.chop(1);
            if(strhexvalue == "")
                strhexvalue = "0";
            newdecvalue = strhexvalue.toLongLong(&ok,2);
        }
            break;
        default:
            break;
        }
        if(ok){
    //        ui->le_hex->setText(QString::number(newdecvalue,16));
    //        ui->le_dec->setText(QString::number(newdecvalue,10));
    //        ui->le_oct->setText(QString::number(newdecvalue,8));
    //        ui->le_bin->setText(QString::number(newdecvalue,2));
            setres(newdecvalue);
        }
    }
}

void calcultor::on_pb_devide_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::devide;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::devide;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_mutiple_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::multiple;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::multiple;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_sub_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::sub;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::sub;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_add_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        this->_nowsympol = _sympol::add;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toULongLong(&ok,10);
        _acaftersympol = true;
    }
    else
    {
        this->_nowsympol = _sympol::add;
        bool ok;
        QString strhexvalue = ui->le_dec->text();
        this->_lastvalue = strhexvalue.toLongLong(&ok,10);
        _acaftersympol = true;
    }
}

void calcultor::on_pb_switch_clicked()
{

}

void calcultor::on_pb_mod_clicked()
{

}

void calcultor::on_pb_equal_clicked()
{
    if (ui->cb_mode->currentText() == "64 BIT U")
    {
        bool ok;
        uint64_t nowvalue = ui->le_dec->text().toULongLong(&ok,10);
        uint64_t res = 0;

        switch (this->_nowsympol) {
        case _sympol::andd:
        {
            res = _lastvalue & nowvalue;
        }
            break;
        case _sympol::orr:
        {
            res = _lastvalue | nowvalue;
        }
            break;
    //    case _sympol::nott:
    //    {
    //        res = !_lastvalue;
    //    }
    //        break;
        case _sympol::xorr:
        {
            res = _lastvalue ^ nowvalue;
        }
            break;
    //    case _sympol::incc:
    //    {
    //        res = _lastvalue++;
    //    }
    //        break;
    //    case _sympol::decc:
    //    {
    //        res = _lastvalue--;
    //    }
    //        break;
        case _sympol::shll:
        {
            res = _lastvalue << nowvalue;
        }
            break;
        case _sympol::shrr:
        {
            res = _lastvalue >> nowvalue;
        }
            break;
    //    case _sympol::roll:
    //    {
    //        res = (_lastvalue << 2) | (_lastvalue >> (sizeof(_lastvalue)*8 - 2));
    //    }
    //        break;
    //    case _sympol::rorr:
    //    {
    //        res = (_lastvalue >> 2) | (_lastvalue << (sizeof(_lastvalue)*8 - 2));
    //    }
    //        break;
        case _sympol::add:
        {
            res = _lastvalue + nowvalue;
        }
            break;
        case _sympol::sub:
        {
            res = _lastvalue - nowvalue;
        }
            break;
        case _sympol::multiple:
        {
            res = _lastvalue * nowvalue;
        }
            break;
        case _sympol::devide:
        {
            res = _lastvalue / nowvalue;
        }
            break;
        case _sympol::none:
            return;
        default:
            return;
        }
        setres(res);
    //    ui->le_hex->setText(QString::number(res,16));
    //    ui->le_dec->setText(QString::number(res,10));
    //    ui->le_oct->setText(QString::number(res,8));
    //    ui->le_bin->setText(QString::number(res,2));
        _nowsympol = _sympol::none;
    }
    else
    {
        bool ok;
        int64_t nowvalue = ui->le_dec->text().toLongLong(&ok,10);
        int64_t res = 0;

        switch (this->_nowsympol) {
        case _sympol::andd:
        {
            res = _lastvalue & nowvalue;
        }
            break;
        case _sympol::orr:
        {
            res = _lastvalue | nowvalue;
        }
            break;
    //    case _sympol::nott:
    //    {
    //        res = !_lastvalue;
    //    }
    //        break;
        case _sympol::xorr:
        {
            res = _lastvalue ^ nowvalue;
        }
            break;
    //    case _sympol::incc:
    //    {
    //        res = _lastvalue++;
    //    }
    //        break;
    //    case _sympol::decc:
    //    {
    //        res = _lastvalue--;
    //    }
    //        break;
        case _sympol::shll:
        {
            res = _lastvalue << nowvalue;
        }
            break;
        case _sympol::shrr:
        {
            res = _lastvalue >> nowvalue;
        }
            break;
    //    case _sympol::roll:
    //    {
    //        res = (_lastvalue << 2) | (_lastvalue >> (sizeof(_lastvalue)*8 - 2));
    //    }
    //        break;
    //    case _sympol::rorr:
    //    {
    //        res = (_lastvalue >> 2) | (_lastvalue << (sizeof(_lastvalue)*8 - 2));
    //    }
    //        break;
        case _sympol::add:
        {
            res = _lastvalue + nowvalue;
        }
            break;
        case _sympol::sub:
        {
            res = _lastvalue - nowvalue;
        }
            break;
        case _sympol::multiple:
        {
            res = _lastvalue * nowvalue;
        }
            break;
        case _sympol::devide:
        {
            res = _lastvalue / nowvalue;
        }
            break;
        case _sympol::none:
            return;
        default:
            return;
        }
        setres(res);
    //    ui->le_hex->setText(QString::number(res,16));
    //    ui->le_dec->setText(QString::number(res,10));
    //    ui->le_oct->setText(QString::number(res,8));
    //    ui->le_bin->setText(QString::number(res,2));
        _nowsympol = _sympol::none;
    }
}

void calcultor::on_pb_dot_clicked()
{

}
