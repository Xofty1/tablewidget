#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QFileInfo>
#include <io.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_AddRow_clicked();

    void on_pushButton_DelRow_clicked();

    void on_spinBox_Row_valueChanged(int arg1);

    void on_pushButton_Sum_clicked();

    void on_pushButton_Random_clicked();



    void on_pushButton_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);


    void on_pushButton_max_clicked();

    void on_pushButton_avg_clicked();

    void on_pushButton_puz_clicked();

    void on_pushButton_proiz_clicked();

    void on_pushButton_addCol_clicked();

    void on_pushButton_DelCol_clicked();

    void on_spinBox_Column_valueChanged(int arg1);

    void on_pushButton_rasch_clicked();

    void on_pushButton_gnom_clicked();

    void on_pushButton_quick_clicked();

    void on_pushButton_sui_clicked();

    void on_pushButton_mon_clicked();

    bool isSorted(int a[], long long n) //функция проверки на сортировку
    {
        while (--n > 0)
            if (a[n] < a[n - 1])
                return false;
        return true;
    }
    bool isSorted_reverse(int a[], long long n) //функция проверки на сортировку
    {
        while (--n > 0)
            if (a[n] > a[n - 1])
                return false;
        return true;
    }

    void shuffle(int a[], long long n) //сортирока
    {
        for (int i = 0; i < n; i++)
            std::swap(a[i], a[rand() % n]);
    }

    void bogosort(int a[], long long n)
    {
        while (!isSorted(a, n))
            shuffle(a, n);
    }
    void quicksort(int mas[],int left , int right);
    void quicksort_reverse(int mas[],int left , int right);


    void on_pushButton_perebor_clicked();



    void on_pushButton_bin_search_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_sort_textChanged();

    void on_pushButton_SaveTXT_clicked();

    void on_pushButton_OpenTXT_clicked();

    void on_pushButton_SaveBIN_clicked();

    void on_pushButton_OpenBIN_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change; //признак НЕ автоматического (ручного) ввода

};

#endif // MAINWINDOW_H
