#include "aboutdialog.h"
#include "qdebug.h"
#include "ui_aboutdialog.h"

AboutDialog* AboutDialog::m_about_dialog_pointer_ = nullptr;
int g_egg_count = 0;

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

AboutDialog *AboutDialog::Instance()
{
    if(nullptr == m_about_dialog_pointer_)
    {
        m_about_dialog_pointer_ = new AboutDialog;
    }
    return m_about_dialog_pointer_;
}

void AboutDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void AboutDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
        event->ignore();
        break;
    }
}

void AboutDialog::on_button_close_clicked()
{
    hide();
}

void AboutDialog::on_lineEdit_cursorPositionChanged()
{
    ui->lineEdit->end(false);
}

//这部分彩蛋有点难懂，写点注释，该槽是在文本框出现字符变化时才调用
//在输入拼音时文本框字符不算出现变化，只有当选定了候选字的时候才触发这个槽函数
void AboutDialog::on_lineEdit_textEdited(const QString str)
{
    //如果输入字数超出彩蛋替换字符的字数，直接锁定文本编辑框
    //g_egg_count是全局的替换字符索引，egg是需要替换的字符串，定义在头文件里
    if(g_egg_count > egg_.count() - 1)
        ui->lineEdit->setEnabled(false);

    //append_char_count计算的是还剩几个字可以添加
    int append_char_count = str.count() - g_egg_count;
    g_egg_count += append_char_count;//将计算结果放入索引

    ui->lineEdit->setText(egg_.mid(0,g_egg_count));//取彩蛋字符串的索引部分来实现字符串替换，该方法的前提是每次光标都得在最后，所以上面做了限制
}

