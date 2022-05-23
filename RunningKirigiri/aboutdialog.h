#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

    static AboutDialog* Instance();

protected:
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:

private slots:
    void on_button_close_clicked();

    void on_lineEdit_cursorPositionChanged();

    void on_lineEdit_textEdited(const QString str);

private:
    Ui::AboutDialog *ui;

    static AboutDialog* m_about_dialog_pointer_;
    const QString       egg_ = "如果键盘不听话的话，你会感到绝望吗？啾咪~";
};
#endif // ABOUTDIALOG_H
