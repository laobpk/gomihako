#ifndef CALCULTOR_H
#define CALCULTOR_H

#include <QWidget>
#include <QMap>
#include <functional>

namespace Ui {
class calcultor;
}

enum _type{
    _hex,
    _dec,
    _oct,
    _bin
};

enum _mode{
    _8bit,_8bitu,
    _16bit,_16bitu,
    _32bit,_32bitu,
    _64bit,_64bitu
};

enum _sympol{
    none=0,
    add,sub,multiple,devide,
    andd,
    orr,
    nott,
    xorr,
    incc,
    decc,
    shll,
    shrr,
    roll,
    rorr
};

class calcultor : public QWidget
{
    Q_OBJECT

public:
    explicit calcultor(QWidget *parent = 0);
    ~calcultor();

private slots:

    void on_cb_mode_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_pb_AC_clicked();

    void on_pb_hex_clicked();

    void on_pb_dec_clicked();

    void on_pb_oct_clicked();

    void on_pb_bin_clicked();

    void on_pb_0_clicked();

    void on_pb_1_clicked();

    void on_pb_2_clicked();

    void on_pb_3_clicked();

    void on_pb_4_clicked();

    void on_pb_5_clicked();

    void on_pb_6_clicked();

    void on_pb_7_clicked();

    void on_pb_8_clicked();

    void on_pb_9_clicked();

    void on_pb_A_clicked();

    void on_pb_B_clicked();

    void on_pb_C_clicked();

    void on_pb_D_clicked();

    void on_pb_E_clicked();

    void on_pb_F_clicked();

    void on_pb_and_clicked();

    void on_pb_or_clicked();

    void on_pb_not_clicked();

    void on_pb_xor_clicked();

    void on_pb_inc_clicked();

    void on_pb_decc_clicked();

    void on_pb_shl_clicked();

    void on_pb_shr_clicked();

    void on_pb_rol_clicked();

    void on_pb_ror_clicked();

    void on_pb_delete_clicked();

    void on_pb_devide_clicked();

    void on_pb_mutiple_clicked();

    void on_pb_sub_clicked();

    void on_pb_add_clicked();

    void on_pb_switch_clicked();

    void on_pb_mod_clicked();

    void on_pb_equal_clicked();

    void on_pb_dot_clicked();

private:
    void addstr(const QString& key);

    void setres(int8_t res);

    void setres(uint8_t res);

    void setres(int16_t res);

    void setres(uint16_t res);

    void setres(int32_t res);

    void setres(uint32_t res);

    void setres(int64_t res);

    void setres(uint64_t res);

private:
    Ui::calcultor *ui;

    int64_t _lastvalue;

    int _nowtype;
    int _nowmode;
    int _nowsympol;
    bool _integer;

    bool _acaftersympol;
};

#endif // CALCULTOR_H
