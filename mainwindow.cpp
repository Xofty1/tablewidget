#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <iostream>
#include <valarray>     // заголовочный файл массивов значений
#include <QDateTime>
#include <QTime>
#include <ctime>
#include <QPixmap>
#include <QProgressBar>
#include <math.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change=true;
    QPixmap pix (":/pix/img/question.png");
    int w = ui-> label_picture-> width();// ширина lable
    int h = ui-> label_picture-> height();// длина label
    ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio)); // размещаем картинку по размеру lable
    //ui-> label_time-> hide();
   //  ui-> label_error-> hide();
    ui-> radioButton_more->click();
    ui->progressBar_deldub->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_AddRow_clicked()//добавить строку
{
    //очищаем все поля , так как изменили таблицу
    ui-> label_Sum-> clear();
    ui-> label_time-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> progressBar_deldub-> setValue(0);
    ui-> label_success-> clear();

    ui-> label_forfind-> clear();
    ui-> listWidget-> clear();
    ui-> label_srav-> clear();
    ui-> listWidget_error-> clear(); // очищаем ListWidget_error
    QPixmap pix (":/pix/img/question.png");
    int w = ui-> label_picture-> width();
    int h = ui-> label_picture-> height();
    ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    //    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->spinBox_Row->setValue(ui->spinBox_Row->value()+1);




}

void MainWindow::on_pushButton_DelRow_clicked() //убрать строку
{
    //очищаем все поля , так как изменили таблицу
    ui-> label_Sum-> clear();
    ui-> label_time-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> label_proiz-> clear();
    ui-> label_success-> clear();
    ui-> progressBar_deldub-> setValue(0);

    ui-> label_forfind-> clear();
    ui-> listWidget-> clear();
     ui-> label_srav-> clear();
     ui-> listWidget_error-> clear(); // очищаем ListWidget_error
     QPixmap pix (":/pix/img/question.png");
     int w = ui-> label_picture-> width();
     int h = ui-> label_picture-> height();
     ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    //    int row=ui->tableWidget->rowCount();

    //    if (row>0)
    //        ui->tableWidget->setRowCount(row-1);
    ui->spinBox_Row->setValue(ui->spinBox_Row->value()-1);
}

void MainWindow::on_spinBox_Row_valueChanged(int arg1) //изменили значение спинбокса
{//очищаем все поля , так как изменили таблицу
    ui-> label_Sum-> clear();
    ui-> label_time-> clear();
    ui-> label_avg-> clear();
    ui-> label_success-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> label_proiz-> clear();
    ui-> label_forfind-> clear();
    ui-> listWidget-> clear();
     ui-> label_srav-> clear();
     ui-> progressBar_deldub-> setValue(0);
     ui-> listWidget_error-> clear(); // очищаем ListWidget_error
     QPixmap pix (":/pix/img/question.png");
     int w = ui-> label_picture-> width();
     int h = ui-> label_picture-> height();
     ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    ui->tableWidget->setRowCount(arg1);



}

void MainWindow::on_pushButton_Sum_clicked() //подсчет суммы
{
    ui-> label_success-> clear();
    no_auto_change=false;
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    int row=ui->tableWidget->rowCount();// считываем количесвто рядов
    int colum=ui->tableWidget->columnCount();// считываем количесвто столбцов

    int sum=0;// начальная сумма
    bool flag; //флаг для определения верности вводимых данных
    bool error = false;// флаг для определения ошибки
    // перебираем все значения
    for (int i=0; i < row; i++)
    {
        for (int j=0; j < colum; j++)
        {
            // получаем указатель на ячейку
            QTableWidgetItem * item = ui-> tableWidget->item(i,j);

            // проверяем, что память под ячейку выделена
            if (item == nullptr)
            {
                item = new QTableWidgetItem();
                ui-> tableWidget-> setItem(i,j,item);

            }
            // получае мзначение
            QString text = item-> text();
            bool flag = false;
            double val = text.toDouble(&flag);
            if (flag) // если знаение корректное
            {
                item -> setBackground (Qt::white);
                sum += val;
            }
            else //если неккоректно
            {
                error = true;
                item -> setBackground (Qt::red);
            }
        }
    }
    if (error)// если ошибка
    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
        ui-> label_Sum-> clear(); // очищаем
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else // если нет ошибки
    {
        if ((row==0) || (colum ==0) ) // если 0 строк и 0 столбцов
        {
            QMessageBox::information (this, "Ошибка", "Нет строк");
            ui-> label_Sum-> clear(); // очищаем
        }

        else
        {
            QPixmap pix (":/pix/img/sum.png");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            ui -> label_Sum -> setNum(sum);
        }
    }
}

void MainWindow::on_pushButton_Random_clicked() //заполнение случайными числами
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
        QTime time = time.currentTime();
    ui-> label_Sum-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> label_proiz-> clear();
    ui-> label_forfind-> clear();

     ui-> label_srav-> clear();
     ui-> listWidget-> clear();
     /*:/pix/img/question.png pix (":/img/random.png");
     int w = ui-> label_picture-> width();
     int h = ui-> label_picture-> height();
     ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));*/
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();
    double place = row *colum;
    int value;
    double progress = 0;
    for (int i=0;i<row;i++)
    {

        for (int j=0;j<colum;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                QTableWidgetItem * ti; //создали указатель
                ti =  new QTableWidgetItem(); //выделяем память
                ui->tableWidget->setItem(i,j,ti); //помещаем ячейку в таблицу
            }
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
            progress += 100/place;
            ui-> progressBar_deldub-> setValue(progress);
            value=rand()%201-100; // от -100 до 100
            ui->tableWidget->item(i,j)->setText(QString::number(value));      
        }

    }
     ui-> progressBar_deldub-> setValue(progress+1);
    no_auto_change=true;
    QPixmap pix (":/pix/img/random.png");
    int w = ui-> label_picture-> width();
    int h = ui-> label_picture-> height();
    ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QTime end = end.currentTime();
    QTime res_second = end.addSecs(-time.second());
    QTime res_msecond = end.addMSecs(-time.msec());
    QTime res (0,0,res_second.second(),res_msecond.msec());
    ui->label_time-> setText(res.toString("ss.zzz"));
}

void MainWindow::on_pushButton_clicked() //min
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    int row=ui->tableWidget->rowCount(); // количество строк
    int colum=ui->tableWidget->columnCount(); // количество столбцов
    int mn ;// переменная для минимума
    ui-> label_min-> clear(); // очищаем
    bool error=false;

    for (int i=0; i < row; i++)
    {
        for (int j=0; j < colum; j++)
        {
            // получаем указатель на ячейку
            QTableWidgetItem * item = ui-> tableWidget->item(i,j);

            // проверяем, что память под ячейку выделена
            if (item == nullptr)
            {

                item = new QTableWidgetItem();
                ui-> tableWidget-> setItem(i,j,item);

            }
            // получаемзначение
            QString text = item-> text();
            //ui-> label_min-> setText(text);
            bool flag = false;
            int val = text.toInt(&flag);
            if (flag) // если знаение корректное
            {
                item -> setBackground (Qt::white);
            }

            else //если неккоректно
            {
                error = true;
                item -> setBackground (Qt::red);
            }
            if (i==0 and j ==0)// 1 элемент теперь саый маленький
            {
                mn = val;
            }

            else if (val <mn) //сравниваем все числа попорядку
            {
                mn=val;
            }
        }
    }

    if (error)

    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
        ui-> label_min-> clear(); // очищаем
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else
    {
        if ((row==0) || (colum ==0) )
        {
            QMessageBox::information (this, "Ошибка", "Нет строк");
            ui-> label_min-> clear(); // очищаем
        }
        else
        {
            QPixmap pix (":/pix/img/minimum.jpg");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            ui -> label_min -> setNum(mn);
        }
    }
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    ui-> label_success-> clear();
   // ui-> label_time-> clear();
    ui-> label_Sum-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> label_proiz-> clear();
    ui-> label_forfind-> clear();


    ui-> listWidget-> clear();
     ui-> label_srav-> clear();
     ui-> listWidget_error-> clear(); // очищаем ListWidget_error
     /*QPixmap pix (":/pix/img/question.png");
     int w = ui-> label_picture-> width();
     int h = ui-> label_picture-> height();
     ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));*/
    QString text = item-> text();
    bool flag = false;
    double val = text.toDouble(&flag);
    if (flag) // если знаение корректное
    {
        item -> setBackground (Qt::white);
    }

    else //если неккоректно
    {
        item -> setBackground (Qt::red);
    }
}

void MainWindow::on_pushButton_max_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();
    double mx ;
    ui-> progressBar_deldub-> setValue(0);
    ui-> label_max-> clear(); // очищаем
    bool error=false;

    for (int i=0; i < row; i++)
    {
        for (int j=0; j < colum; j++)
        {
            // получаем указатель на ячейку
            QTableWidgetItem * item = ui-> tableWidget->item(i,j);

            // проверяем, что память под ячейку выделена
            if (item == nullptr)
            {
                item = new QTableWidgetItem();
                ui-> tableWidget-> setItem(i,j,item);

            }
            // получаемзначение
            QString text = item-> text();


            ui-> label_max-> setText(text);


            bool flag = false;
            double val = text.toDouble(&flag);

            if (flag) // если знаение корректное
            {
                item -> setBackground (Qt::white);

            }

            else //если неккоректно
            {
                error = true;
                item -> setBackground (Qt::red);
            }
            if (i==0 and j ==0)// 1 элемент теперь самый маленький
            {
                mx = val;
            }

            else if (val >mx) //сравниваем все числа попорядку
            {
                mx=val;
            }
        }
    }

    if (error)

    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
        ui-> label_max-> clear(); // очищаем
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else
    {
        if ((row==0) || (colum ==0) )
        {
            QMessageBox::information (this, "Ошибка", "Нет строк");
            ui-> label_max-> clear(); // очищаем
        }
        else
        {
            ui -> label_max -> setNum(mx);
            QPixmap pix (":/pix/img/maximum.jpg");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        }
    }
}

void MainWindow::on_pushButton_avg_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
  /*  int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();
    double avg ;
    ui-> label_avg-> clear(); // очищаем
    bool error=false;

    for (int i=0; i < row; i++)
    {
        for (int j=0; j < colum; j++)
        {
            // получаем указатель на ячейку
            QTableWidgetItem * item = ui-> tableWidget->item(i,j);

            // проверяем, что память под ячейку выделена
            if (item == nullptr)
            {
                item = new QTableWidgetItem();
                ui-> tableWidget-> setItem(i,j,item);

            }
            // получаемзначение
            QString text = item-> text();


            ui-> label_avg-> setText(text);


            bool flag = false;
            double val = text.toDouble(&flag);

            if (flag) // если знаение корректное
            {
                item -> setBackground (Qt::white);

            }

            else //если неккоректно
            {
                error = true;
                item -> setBackground (Qt::red);
            }
            avg += val;

        }

        if (error)

        {
            QMessageBox::information (this, "Ошибка", "Введены неверные значения");
            ui-> label_avg-> clear(); // очищаем
        }
        else
        {
            if ((row==0) || (colum ==0) )
            {
                QMessageBox::information (this, "Ошибка", "Нет строк");
                ui-> label_max-> clear(); // очищаем
            }
            else
                ui -> label_avg -> setNum(avg/(row *colum));
        }
    }
}*/

       /* no_auto_change=false;
        int row=ui->tableWidget->rowCount();
        int colum=ui->tableWidget->columnCount();

        double sum=0;
        bool flag;
        bool error = false;
        for (int i=0;i<row;i++)
            for (int j=0;j<colum;j++)
                if (ui->tableWidget->item(i,j)!=nullptr) //проверка существования ячейки
                {//есть ячейка

                    sum+=ui->tableWidget->item(i,j)->text().toInt(&flag);
                    if (!flag)
                        error = true;
                    if (flag)
                        ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
                    else
                        ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
                }
                else
                { // нет ячейки
                    //создаем
                    QTableWidgetItem * ti; //создали указатель
                    ti =  new QTableWidgetItem(); //выделяем память
                    ui->tableWidget->setItem(i,j,ti); //помещаем ячейку в таблицу
                    //красим
                    ui->tableWidget->item(i,j)->setBackgroundColor(Qt::blue);
                }

        if (error)

        {
            QMessageBox::information (this, "Ошибка", "Введены неверные значения");
            ui-> label_avg-> clear(); // очищаем
        }
        else
        {
            if ((row==0) || (colum ==0) )
            {
                QMessageBox::information (this, "Ошибка", "Нет строк");
                ui-> label_avg-> clear(); // очищаем
            }
            else
                ui -> label_avg -> setNum(sum/(row *colum));
        }
    }*/
    double avg=0;
    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount();

    bool error=false;
    bool flag;
    for (int i=0 ;i<row;i++)
        for (int j=0 ; j<column; j++)
        {
            QTableWidgetItem *item = ui-> tableWidget->item(i,j);
            if (ui-> tableWidget-> item(i,j)==nullptr)
            {

                item = new QTableWidgetItem;
                ui-> tableWidget-> setItem(i,j,item);
            }

            QString text = item-> text();
            double val = text.toInt(&flag);
            if (!flag)
            {
                error = true;
                item -> setBackground (Qt::red);
            }

            else
            {
                avg += val;
            }


        }
    if (error)
    {
        QMessageBox::information(this, "Ошибка", "Неверно введены значения");
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    }
    else
    {
        QPixmap pix (":/pix/img/avg.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui-> label_avg-> setNum(avg/(row*column));
    }
}
void MainWindow::on_pushButton_puz_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();


    double progress = 0;

    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount()-1;
    double place = row *(column+1);
    QString q;
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");

    }
    double *mas;

    mas = new double[row];
    bool flag;

    int bad_value=-1;
    bool error = false;
    for (int i = 0; i<row; i++)
    {

        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {

            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;


                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                q +=  QString:: number(bad_value+1) +" ";
                mas[bad_value]= 98989;
            }


            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }

    }

    if ((!error) and ui->radioButton_more->isChecked() )
    {

        int i = 0;
        while (i < row -1)
        {

            int j = i+1;
            while (j<row)
            {
                progress += 100/place;
                ui-> progressBar_deldub-> setValue(progress);
                if (mas[i] > mas[j])
                {
                    double tim = mas[i];
                    mas[i] = mas[j];
                    mas[j] = tim;

                }
                j+=1;
            }
            i+=1;
        }
        progress = 100;
         ui-> progressBar_deldub-> setValue(progress);
        QPixmap pix (":/pix/img/bubble.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));
    }
    else if ((!error) and ui->radioButton_less->isChecked())
    {
        int i = 0;
        while (i < row -1)
        {
            int j = i+1;
            while (j<row)
            {
                progress += 100/place;
                ui-> progressBar_deldub-> setValue(progress);
                if (mas[i] < mas[j])
                {
                    double tim = mas[i];
                    mas[i] = mas[j];
                    mas[j] = tim;

                }
                j+=1;
            }
            i+=1;
        }
        progress = 100;
         ui-> progressBar_deldub-> setValue(progress);
        QPixmap pix (":/pix/img/bubble.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));
    }
    else
    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");


        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    }
    int x = 0;

    while (x< row)
    {
        if (mas[x] == 98989)
        {
            ui-> tableWidget-> item(x,0)-> setText("Ошибка");
        }
        else
        {
            ui-> tableWidget-> item(x,0)-> setText(QString::number(mas[x]));
        }

        x+=1;
    }



    delete [] mas;
    mas = nullptr;


}
//ui-> tableWidget-> item(i,0)-> setText(QString::number(mass[i]));
void MainWindow::on_pushButton_proiz_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int colum=ui->tableWidget->columnCount();

    int proiz=1;
    bool flag;
    bool error = false;
    for (int i=0;i<row;i++)
        for (int j=0;j<colum;j++)
            if (ui->tableWidget->item(i,j)!=nullptr) //проверка существования ячейки
            {//есть ячейка

                proiz*=ui->tableWidget->item(i,j)->text().toInt(&flag);
                if (!flag)
                    error = true;

                if (flag)
                    ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
                else
                    ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
            }
            else
            { // нет ячейки
                //создаем
                QTableWidgetItem * ti; //создали указатель
                ti =  new QTableWidgetItem(); //выделяем память
                ui->tableWidget->setItem(i,j,ti); //помещаем ячейку в таблицу
                //красим
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::blue);
            }

    if (error)

    {

        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
        ui-> label_Sum-> clear(); // очищаем
    }
    else
    {

        if ((row==0) || (colum ==0) )
        {
            QMessageBox::information (this, "Ошибка", "Нет строк");
            ui-> label_proiz-> clear(); // очищаем
        }
        else
        {
            QPixmap pix (":/pix/img/proiz.jpg");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            ui -> label_proiz -> setNum(proiz);
        }
    }
}

void MainWindow::on_pushButton_addCol_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    ui-> label_Sum-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();
    ui-> listWidget-> clear();
    ui-> listWidget_error-> clear(); // очищаем ListWidget_error
    ui->spinBox_Column->setValue(ui->spinBox_Column->value()+1);
}

void MainWindow::on_pushButton_DelCol_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    ui-> label_Sum-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();

    ui-> listWidget-> clear();
    ui-> listWidget_error-> clear(); // очищаем ListWidget_error

    ui->spinBox_Column->setValue(ui->spinBox_Column->value()-1);
}

void MainWindow::on_spinBox_Column_valueChanged(int arg1)
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    ui-> progressBar_deldub-> setValue(0);
    ui-> label_Sum-> clear();
    ui-> label_avg-> clear();
    ui-> label_max-> clear();
    ui-> label_min-> clear();

    ui-> listWidget-> clear();
    ui-> listWidget_error-> clear(); // очищаем ListWidget_error
    ui->tableWidget->setColumnCount(arg1);
    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount();
    if (row*column >1000000)
    {
       column = 1;
       QMessageBox::information (this, "Ошибка", "Количество ячеек не может быть больше 1000000");
         ui-> spinBox_Column-> setValue(1);
    }

    ui->tableWidget->setColumnCount(column);

}

void MainWindow::on_pushButton_rasch_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    QString q;
    int row = ui-> tableWidget-> rowCount();

    int column = ui-> tableWidget-> columnCount()-1;
    double progress = 0;
    double place = row *(column +1);
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");

    }
    double *mas;
    bool flag;
    mas = new double[row];

    int bad_value=-1;




    bool error = false;
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                mas[bad_value]= 98989;
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                q+=QString:: number(bad_value+1)+" ";
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }

    }

    if ((!error) and ui->radioButton_more->isChecked())
    {
        QPixmap pix (":/pix/img/расческа.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int step = row-1;
        double gold = 1.247;

        while (step >= 1) {
            for (int i = 0; i + step < row; ++i) {

              if (mas[i] > mas[i + step]) {
                swap(mas[i], mas[i + step]);
              }
            }
            step /= gold;
          }
          // сортировка пузырьком
          for (int i = 0; i + 1 < row; ++i) {
            for (int j = 0; j + 1 < row - i; ++j) {
                progress += 100/place;
                 ui-> progressBar_deldub-> setValue(progress);

              if (mas[j + 1] < mas[j]) {
                swap(mas[j], mas[j + 1]);
              }
            }
          }

        /*int step = row-1;
        double gold = 1.247;
        bool is_swap=true;

        while ((step >1) || (is_swap))
        {

            step = step / gold;


            is_swap = false;
            int i = 0;

            int stepInt = step;
            while (i+stepInt <row)
            {
                if (mas[i] > mas[i+stepInt])
                {
                    double tim = mas[i];
                    mas[i] = mas[i+stepInt];
                    mas[i+stepInt] = tim;
                    is_swap = true;

                }
                i+=1;
            }
        }*/
          ui-> progressBar_deldub-> setValue(100);
          QTime end = end.currentTime();
          QTime res_second = end.addSecs(-time.second());
          QTime res_msecond = end.addMSecs(-time.msec());
          QTime res (0,0,res_second.second(),res_msecond.msec());
          ui->label_time-> setText(res.toString("ss.zzz"));

    }

   else if ((!error) and ui->radioButton_less->isChecked())
    {
        QPixmap pix (":/pix/img/расческа.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int step = row-1;
        double gold = 1.247;

        while (step >= 1) {
            for (int i = 0; i + step < row; ++i) {
              if (mas[i] > mas[i + step]) {
                swap(mas[i], mas[i + step]);
              }
            }
            step /= gold;
          }
          // сортировка пузырьком
          for (int i = 0; i + 1 < row; ++i) {
            for (int j = 0; j + 1 < row - i; ++j) {
                progress += 100/place;
                 ui-> progressBar_deldub-> setValue(progress);
              if (mas[j + 1] > mas[j]) {
                swap(mas[j], mas[j + 1]);
              }
            }

          }
          ui-> progressBar_deldub-> setValue(100);
          QTime end = end.currentTime();
          QTime res_second = end.addSecs(-time.second());
          QTime res_msecond = end.addMSecs(-time.msec());
          QTime res (0,0,res_second.second(),res_msecond.msec());
          ui->label_time-> setText(res.toString("ss.zzz"));

    }

    else
    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");


        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк


    }

    int x = 0;

    while (x< row)
    {
        if (mas[x] == 98989)
        {
            ui-> tableWidget-> item(x,0)-> setText("Ошибка");
        }
        else
        {
            ui-> tableWidget-> item(x,0)-> setText(QString::number(mas[x]));
        }

        x+=1;
    }

    delete [] mas;
    mas = nullptr;

}

void MainWindow::on_pushButton_gnom_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    QString q;
    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount()-1;
    double progress = 0;
    double place = row * (column+1);

    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");

    }
    double *mas;

    mas = new double[row];
    bool flag;
    int bad_value=-1;
    bool error = false;
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr) //если существует
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
                q+=QString:: number(bad_value+1)+" ";
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }

    }

    if (!error and ui-> radioButton_more-> isChecked())
    {
        QPixmap pix (":/pix/img/gnom.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int i = 0;
        while (i < row)
        {
            progress += 100/place;
             ui-> progressBar_deldub-> setValue(progress);
            if ( i ==0 || mas[i-1] <= mas[i])
            {
                i+=1;

            }
            else
            {
                int j = i-1;
                double tim = mas[i];
                mas[i] = mas[j];
                mas[j] = tim;
                i = j;


            }
        }
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));
    }
    else if (!error and ui-> radioButton_less-> isChecked()) //по убыванию
    {
        QPixmap pix (":/pix/img/gnom.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int i = 0;
        while (i < row)
        {
            progress += 100/place;
             ui-> progressBar_deldub-> setValue(progress);
            if ( i ==0 || mas[i-1] >= mas[i])
            {
                i+=1;

            }
            else
            {
                int j = i-1;
                double tim = mas[i];
                mas[i] = mas[j];
                mas[j] = tim;
                i = j;


            }
        }
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));

    }
    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");

        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк


    }
    int x = 0;


    while (x< row)
    {
        if (mas[x] == 98989)
        {
            ui-> tableWidget-> item(x,0)-> setText("Ошибка");
        }
        else
        {
            ui-> tableWidget-> item(x,0)-> setText(QString::number(mas[x]));
        }

        x+=1;
    }


    delete [] mas;
    mas = nullptr;
}

void MainWindow:: quicksort(int mas[],int left , int right)
{


    int time_start= clock();


    int i = left;
    int j = right;
    double pivot =  mas[(left + right) / 2];
       do
       {

           while((mas[i] < pivot) and (i < right))
           {
               i++;
           }
           while((pivot < mas[j]) and (j > left))
           {
               j--;
           }
           if(i <= j)
           {
               double tmp = mas[i];
               mas[i] = mas[j];
               mas[j] = tmp;
               i++;
               j--;
           }
       } while(i <= j);

       if(left < j)
       {
           quicksort(mas, left, j);
       }
       if(i < right)
       {
           quicksort(mas, i, right);
       }

       int time_end = clock();
       int time = -time_start +time_end;
       ui-> label_time-> setNum(time);
}

void MainWindow:: quicksort_reverse(int mas[],int left , int right)
{


    int time_start= clock();


    int i = left;
    int j = right;
    double pivot =  mas[(left + right) / 2];
       do
       {

           while((mas[i] > pivot) and (i < right))
           {
               i++;
           }
           while((pivot > mas[j]) and (j > left))
           {
               j--;
           }
           if(i <= j)
           {
               double tmp = mas[i];
               mas[i] = mas[j];
               mas[j] = tmp;
               i++;
               j--;
           }
       } while(i <= j);

       if(left < j)
       {
           quicksort_reverse(mas, left, j);
       }
       if(i < right)
       {
           quicksort_reverse(mas, i, right);
       }

       int time_end = clock();
       int time = -time_start +time_end;
       ui-> label_time-> setNum(time);
}

void MainWindow::on_pushButton_quick_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    ui-> progressBar_deldub-> setValue(0);
    QString q;
    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount()-1;
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");

    }
    int *mas = new int[row];
    bool flag;
    int bad_value=-1;
    bool error = false;
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }


    }

    if (!error and ui-> radioButton_more-> isChecked())
    {

        

        quicksort(mas, 0, row-1);

        QPixmap pix (":/pix/img/fast.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));

    }
    else if (!error and ui-> radioButton_less-> isChecked())
    {
        quicksort_reverse(mas, 0, row-1);

        QPixmap pix (":/pix/img/fast.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QTime end = end.currentTime();
        QTime res_second = end.addSecs(-time.second());
        QTime res_msecond = end.addMSecs(-time.msec());
        QTime res (0,0,res_second.second(),res_msecond.msec());
        ui->label_time-> setText(res.toString("ss.zzz"));

    }
    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");

        q+= QString :: number(bad_value+1) + " ";
        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк

    }

    int x = 0;

    while (x< row)
    {
        if (mas[x] == 98989)
        {
            ui-> tableWidget-> item(x,0)-> setText("Ошибка");
        }
        else
        {
            ui-> tableWidget-> item(x,0)-> setText(QString::number(mas[x]));
        }

        x+=1;
    }

    delete [] mas;
    mas = nullptr;

}

void MainWindow::on_pushButton_sui_clicked()
{
    ui-> label_success-> clear();
    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount();
    double *mas;

    mas = new double[row];
    bool flag;

    int bad_value_row=-1;
    int bad_value_column=-1;




    bool error = false;
    for (int i = 0; i<row; i++)
        for (int j = 0; j<column; j++)
    {
        if (ui->tableWidget->item(i,j)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,j)->text().toInt(&flag);
            if (!flag)
            {
                error = true;

                bad_value_row= i;
                bad_value_column=j;
                ui-> tableWidget-> item(bad_value_row,bad_value_column)-> setText("Ошибка");
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
                mas[bad_value_row*bad_value_column]= 98989;
            }

            else
            {
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,j,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::blue);

        }

    }

    if (!error)
    {
        int i = 0;
        while (i < (row *column) -1)
        {
            int j = i+1;
            while (j<(row*column))
            {
                if (mas[i] > mas[j])
                {
                    double tim = mas[i];
                    mas[i] = mas[j];
                    mas[j] = tim;

                }
                j+=1;
            }
            i+=1;
        }
    }
    else
    {
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");


    }


    for (int x=1;x<row;x++)
        for (int y = 0; y <column;y++)



        {
            if (mas[x*y] == 98989)
            {
                ui-> tableWidget-> item(x%row,y%column)-> setText("Ошибка");
            }
            else
            {
                ui-> tableWidget-> item(x%row,y%column)-> setText(QString::number(mas[x*y]));

            }


        }
}

void MainWindow::on_pushButton_mon_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();

    ui-> progressBar_deldub-> setValue(0);
    QString q;
    int time_start = clock();
    QDateTime start = QDateTime::currentDateTime();

    int row = ui-> tableWidget-> rowCount();
    int column = ui-> tableWidget-> columnCount()-1;
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");

    }


    int *mas = new int[row];
    bool flag;

    int bad_value=-1;


    bool error = false;
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
                q += QString :: number(bad_value+1) +" " ;
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }

    }
    bool more = false; // переменная для определения типа сортировки
    bool less = false; // переменная для определения типа сортировки
    if (!error and ui-> radioButton_more->isChecked())
    {
        more = true;
        QPixmap pix (":/pix/img/monkey1.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

        int count = 0;

        while (count <=10000000)
        {
            int ran1 = rand()%row;
            int ran2 = ran1-1;
            if (ran1 == 0)
                break;


            if (mas[ran1] < mas[ran2])
            {
                double tim = mas[ran1];
                mas[ran1] = mas[ran2];
                mas[ran2] = tim;

            }
            count +=1;
        }
    }

    else if (!error and ui-> radioButton_less->isChecked())
    {
        less = true;
         QPixmap pix (":/pix/img/monkey1.jpg");
         int w = ui-> label_picture-> width();
         int h = ui-> label_picture-> height();
         ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

         int count = 0;

         while (count <=10000000)
         {
             int ran1 = rand()%row;
             int ran2 = ran1-1;
             if (ran1 == 0)
                 break;


             if (mas[ran1] > mas[ran2])
             {
                 double tim = mas[ran1];
                 mas[ran1] = mas[ran2];
                 mas[ran2] = tim;

             }
             count +=1;
         }
    }
    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");

        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк


    }
    int x = 0;

    while (x< row)
    {
        if (mas[x] == 98989)
        {
            ui-> tableWidget-> item(x,0)-> setText("Ошибка");
        }
        else
        {
            ui-> tableWidget-> item(x,0)-> setText(QString::number(mas[x]));
        }

        x+=1;
    }
    bool isSort= true;
    for (int i =0; i<row-1;i++)
    {
        if (mas[i]>mas[i+1]and more)
        {
             isSort = false;
        }
        if (mas[i]<mas[i+1]and less)
        {
             isSort = false;
        }

    }
    if (isSort)
         ui-> label_success->setText("Сортировка прошла успешна");
    else
         ui-> label_success->setText("Сортировка прошла не до конца");


     QDateTime finish = QDateTime::currentDateTime();
  //   ui-> label_time-> setText(QTime::currentTime().toString('hh:mm:ss'));
     int end_time= clock();
     int time = end_time -time_start;
     ui-> label_time-> setNum(time/1000);
     delete [] mas;
     mas = nullptr;
     if (error)
     {
         ui-> label_time-> clear();
         ui-> label_success-> clear();
     }
}

void MainWindow::on_pushButton_perebor_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    ui-> progressBar_deldub-> setValue(0);
    int time_start= clock();
    bool flag;
    ui-> label_forfind-> clear();

    int find_num = ui-> lineEdit_sort-> text().toInt(&flag);

    int row = ui-> tableWidget-> rowCount();
    int column = 0;

    int *mas = new int [row];
    int bad_value = -1;
    /*if (flag)
    {
        for (int i =0; i < row; i++)
        {
            if (find_num == mas[i])
            {
                ui-> label_error-> setNum(i+1);
            }
        }

    }*/

    double place = row;
    bool error = false;
    if (flag)
    {
    for (int i = 0; i<row; i++)
    {

        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }


    }
    QString q;
    bool isIn = false;
    if (!error)
    {
        QPixmap pix (":/pix/img/perebor.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int count = 0;
        if (!isSorted(mas,row))
        {
            for (int i =0; i < row; i++)
            {


                count +=1;
                if (find_num == mas[i])
                {
                    isIn = true;
                    ui-> label_forfind-> setNum(i+1);
                    q +=  QString:: number(i+1) +" ";
                    ui->tableWidget->item(i,column)->setBackgroundColor(Qt::green);
                }
            }
        }
        else
        {

            for (int i =0; i < row; i++)
            {



                if (find_num>=mas[i])
                {
                    count +=1;
                    if (find_num == mas[i])
                    {
                        isIn = true;
                        q +=  QString:: number(i+1) +" ";

                    }
                }
                else
                {
                    break;
                }
            }

        }
        if (isIn)
        {
            ui-> listWidget-> clear();
            ui-> listWidget-> addItem(q);
            ui-> label_srav-> setNum(count);
            QTime end = end.currentTime();
            QTime res_second = end.addSecs(-time.second());
            QTime res_msecond = end.addMSecs(-time.msec());
            QTime res (0,0,res_second.second(),res_msecond.msec());
        //    if (ui->label_time->text().size() == 0)
            ui->label_time-> setText(res.toString("ss.zzz"));
        }
        else
        {
            QPixmap pix (":/pix/img/notsorted.png");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            ui->label_success->setText("Такого значени нет!");
        }
//        QTime end = end.currentTime();
//        QTime res_second = end.addSecs(-time.second());
//        QTime res_msecond = end.addMSecs(-time.msec());
//        QTime res (0,0,res_second.second(),res_msecond.msec());
//    //    if (ui->label_time->text().size() == 0)
//        ui->label_time-> setText(res.toString("ss.zzz"));
    }


    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");


    }
//    QTime end = end.currentTime();
//    QTime res_second = end.addSecs(-time.second());
//    QTime res_msecond = end.addMSecs(-time.msec());
//    QTime res (0,0,res_second.second(),res_msecond.msec());
//    ui->label_time-> setText(res.toString("ss.zzz"));
    }
    else{
        ui->label_time-> setText("Ошибка");

    }
    delete [] mas;
    mas = nullptr;


}

void MainWindow::on_pushButton_bin_search_clicked()
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    ui-> progressBar_deldub-> setValue(0);
    int time_start = clock();
    bool flag;
    ui-> label_forfind-> clear();

    int find_num = ui-> lineEdit_sort-> text().toInt(&flag);

    int row = ui-> tableWidget-> rowCount();
    int column = 0;
    int *mas = new int [row];
    int bad_value = -1;

    bool error = false;
    if (flag)
    {
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }


    }
    QString q;
    if (!error)
    {
        QPixmap pix (":/pix/img/bin.jpg");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        int count = 0;
        if (isSorted(mas,row))
        {

            int l = 0;
            int r = row; // в этом случае присваивается именно n
            int mid;

            while (l < r)
            {
                count+=1;
                mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]

                if (mas[mid] > find_num)
                    r = mid; // проверяем, какую часть нужно отбросить с поиска
                else if (mas[mid] < find_num)
                    l = mid+1;
                else
                    break;
            }
            if (mas[mid]!=find_num)
            {
                QPixmap pix (":/pix/img/notsorted.png");
                int w = ui-> label_picture-> width();
                ui-> label_srav->clear();
                ui-> listWidget->clear();
                int h = ui-> label_picture-> height();
                ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                ui->label_success->setText("Такого значени нет!");
            }
            else{


            while (mas[mid]==find_num)
            {
                mid-=1;
            }
            mid+=1;
            while (mas[mid]==find_num)
            {
                q +=  QString:: number(mid+1) +" ";
                mid+=1;
                ui-> label_srav-> setNum(count);
            }
            ui-> listWidget-> clear();
            ui-> listWidget-> addItem(q);
            QTime end = end.currentTime();
            QTime res_second = end.addSecs(-time.second());
            QTime res_msecond = end.addMSecs(-time.msec());
            QTime res (0,0,res_second.second(),res_msecond.msec());
        //    if (ui->label_time->text().size() == 0)
            ui->label_time-> setText(res.toString("ss.zzz"));
            }
        }
       else if (isSorted_reverse(mas,row))
        {


            int l = 0;
            int r = row; // в этом случае присваивается именно n
            int mid;

            while (l < r)
            {
                count+=1;
                mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]

                if (mas[mid] < find_num)
                    r = mid; // проверяем, какую часть нужно отбросить с поиска
                else if (mas[mid] > find_num)
                    l = mid+1;
                else
                    break;
            }
            if (mas[mid]!=find_num)
            {
                QPixmap pix (":/pix/img/notsorted.png");
                int w = ui-> label_picture-> width();
                ui-> label_srav->clear();
                ui-> listWidget->clear();
                int h = ui-> label_picture-> height();
                ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
                ui->label_success->setText("Такого значени нет!");
            }
            else{


            while (mas[mid]==find_num)
            {
                mid-=1;
            }
            mid+=1;
            while (mas[mid]==find_num)
            {
                q +=  QString:: number(mid+1) +" ";
                mid+=1;
                ui-> label_srav-> setNum(count);
            }
            ui-> listWidget-> clear();
            ui-> listWidget-> addItem(q);
            QTime end = end.currentTime();
            QTime res_second = end.addSecs(-time.second());
            QTime res_msecond = end.addMSecs(-time.msec());
            QTime res (0,0,res_second.second(),res_msecond.msec());
        //    if (ui->label_time->text().size() == 0)
            ui->label_time-> setText(res.toString("ss.zzz"));
            }


        }

        else
        {
            QMessageBox::information(this,"Ошибка","Отсортируйте список!");
        }
    }
    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
    }
//    QTime end = end.currentTime();
//    QTime res_second = end.addSecs(-time.second());
//    QTime res_msecond = end.addMSecs(-time.msec());
//    QTime res (0,0,res_second.second(),res_msecond.msec());
////    if (ui->label_time->text().size() == 0)
//    ui->label_time-> setText(res.toString("ss.zzz"));
    }
    else{
        ui->label_time-> setText("Ошибка");

    }
    delete [] mas;
    mas = nullptr;

}

void MainWindow::on_pushButton_2_clicked()// удаление дубликатов
{
    ui-> label_success-> clear();
    ui-> label_time-> clear();
    QTime time = time.currentTime();
    ui-> progressBar_deldub-> setValue(0);

    QString q;
    int time_start= clock();
    bool flag;
    ui-> label_forfind-> clear();

    int row = ui-> tableWidget-> rowCount();
    int column = 0;
    int *mas = new int [row];
    int bad_value = -1;

  //  ui->progressBar_deldub->setValue(0);


    bool error = false;
    for (int i = 0; i<row; i++)
    {
        QTableWidgetItem * item = ui-> tableWidget->item(i,column);

        // проверяем, что память под ячейку выделена
        if (item == nullptr)
        {

            item = new QTableWidgetItem();
            ui-> tableWidget-> setItem(i,column,item);

        }
        if (ui->tableWidget->item(i,column)!=nullptr)
        {
            mas[i] = ui->tableWidget->item(i,column)->text().toInt(&flag);
            if (mas[i]>100)
                mas[i]= 98989;
            if (!flag)
            {
                error = true;

                bad_value= i;
                ui-> tableWidget-> item(bad_value,0)-> setText("Ошибка");
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::red);
                mas[bad_value]= 98989;
                q += QString ::number(bad_value+1)+" ";
            }

            else
            {
                ui->tableWidget->item(i,column)->setBackgroundColor(Qt::white);
            }

        }
        else
        {
            QTableWidgetItem * ti; //создали указатель
            ti =  new QTableWidgetItem(); //выделяем память
            ui->tableWidget->setItem(i,column,ti); //помещаем ячейку в таблицу
            //красим
            ui->tableWidget->item(i,column)->setBackgroundColor(Qt::blue);

        }


    }


    if (!error)
    {
        if (isSorted(mas,row) or isSorted_reverse(mas,row))
        {
            QPixmap pix (":/pix/img/deletedb.jpg");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
            int row_ynic = 1;

            for (int i =0; i < row-1; i++)
            {

                int first = mas[i];
                if (first != mas[i+1])
                {
                    row_ynic +=1;
                }
            }
            ui->tableWidget->setRowCount(row_ynic);
            int *mas_ynic = new int [row_ynic];
            int k= 1;
            mas_ynic[0]= mas[0];
            for (int i=0; i<row-1 ; i++)
            {

                if (mas[i] != mas[i+1])
                {

                    mas_ynic[k] = mas[i+1];
                    ui-> tableWidget-> item(k,0)-> setText(QString::number(mas_ynic[k]));
                    k++;

                }
            }
           // ui-> tableWidget-> item(k,0)-> setText(QString::number(mas_ynic[k]));
        }
      else if (!(isSorted(mas,row)) or !(isSorted_reverse(mas,row)))
        {
            QPixmap pix (":/pix/img/notsorted.png");
            int w = ui-> label_picture-> width();
            int h = ui-> label_picture-> height();
            ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
             QMessageBox::information (this, "Ошибка", "Отсортируйте список!");

        }
    }
    else
    {
        QPixmap pix (":/pix/img/error.png");
        int w = ui-> label_picture-> width();
        int h = ui-> label_picture-> height();
        ui -> label_picture-> setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        QMessageBox::information (this, "Ошибка", "Введены неверные значения");
        ui-> listWidget_error-> clear(); // очищаем ListWidget_error
        ui-> listWidget_error-> addItem(q); // вводим новое значение ошибочных строк




    }
    QTime end = end.currentTime();
    QTime res_second = end.addSecs(-time.second());
    QTime res_msecond = end.addMSecs(-time.msec());
    QTime res (0,0,res_second.second(),res_msecond.msec());
    ui->label_time-> setText(res.toString("ss.zzz"));
    ui-> spinBox_Row-> setValue(ui-> tableWidget-> rowCount());
    delete [] mas;
    mas = nullptr;


}

void MainWindow::on_lineEdit_sort_textChanged()
{
    ui-> label_success-> clear();
    ui-> progressBar_deldub-> setValue(0);
    bool flag;
    int find_num = ui-> lineEdit_sort->text(). toInt(&flag);
    if (!flag)
    {
        ui-> lineEdit_sort-> setStyleSheet("color: red;font-size: 19px");

    }
    else
    {
        ui-> lineEdit_sort-> setStyleSheet("color: black; font-size: 19px");
    }
}

void MainWindow::on_pushButton_SaveTXT_clicked()// сохранение текстового файла
{
    int column = ui-> tableWidget-> columnCount()-1;
//    int size_int = sizeof(int);
//    int controlsum = 0;
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");
        return;

    }
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как txt"),"C:\\Users\\student.GIS\\Downloads\\", tr("Text files (*.txt)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Ошибка", "Файл не выбран");
    }
    else
    {
        QFileInfo fi = fileName;
        QString ext = fi.completeSuffix();
        if (ext != "txt")
        {
            QMessageBox::information(this, "Ошибка", "Неверный формат");
            return;
        }
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);

        QString str;
        int size = ui-> spinBox_Row-> value();
        str.setNum(size);
        str.append("\n");

        file.write(str.toUtf8());

        for (int i = 0; i< size; i++)
        {
            if (ui->tableWidget-> item(i,0) == nullptr)
            {
                QTableWidgetItem * ti ;
                ti = new QTableWidgetItem;
                ui-> tableWidget-> setItem(i,0,ti);

            }
            str =ui-> tableWidget-> item(i,0)-> text();
//            int num = ui-> tableWidget-> item(i,0) -> text().toInt();
            str.append("\n");
            file.write(str.toUtf8());
//            controlsum += num;


        }
//        char *mas;
//        memcpy (mas, &controlsum, size_int);
//        file.write(str.toUtf8());
        file.close();

    }
}

void MainWindow::on_pushButton_OpenTXT_clicked()// текстового файла
{
    QString fileName;
    int controlsum = 0;
    int size_char = sizeof(char);
    fileName = QFileDialog::getOpenFileName(this, tr("Открыть txt"),"C:\\Users\\student.GIS\\Downloads\\", tr("Text files (*.txt)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Ошибка", "Файл не выбран");
    }
    else
    {
        QFileInfo fi = fileName;
        QString ext = fi.completeSuffix();
        if (ext != "txt")
        {
            QMessageBox::information(this, "Ошибка", "Неверный формат");
            return;
        }
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);

        QString str;
        int size;
        QByteArray ba;
        bool flag;
        ba = file.readLine();
        str.clear();
        str.append(ba);
        str.remove("\n");
        size = str.toInt(&flag);



        if (!flag)
        {
            QMessageBox::information (this,"Ошбка", "Неправильно");
        }

        else{
            ui-> spinBox_Row-> setValue(size);
            for (int i = 0; i< size; i++)
            {


                ba = file.readLine();






            }
            ba = file.readLine();
            if (!ba.isNull())
            {
                QMessageBox::information(this, "Ошибка", "Поврежденный файл");
                return;
            }

            file.close();
            QFile file1;
            file1.setFileName(fileName);
            file1.open(QIODevice::ReadOnly);
            ba = file1.readLine();
            for (int i = 0; i< size; i++)
            {
                if (ui->tableWidget-> item(i,0) == nullptr)
                {
                    QTableWidgetItem * ti ;
                    ti = new QTableWidgetItem;
                    ui-> tableWidget-> setItem(i,0,ti);

                }

                ba = file1.readLine();
                str.clear();
                str.append(ba);


                ui-> tableWidget-> item(i,0)-> setText(str);




            }
            file1.close();
//         /*   ba = file.readLine();
//            if (!ba.isNull())
//            {
//                 QMessageBox::information(this, "Ошибка", "Поврежденный файл");
////                 ui-> spinBox_Row-> setValue(0);
////                 ui->tableWidget->clear();
//            }*/


        }






    }
}

void MainWindow::on_pushButton_SaveBIN_clicked()// сохранение бинарного файла
{

    int column = ui-> tableWidget-> columnCount()-1;
    int controlsum = 0;
    if (column !=0)
    {
        column =0;
        ui->tableWidget->setColumnCount(1);
        ui-> spinBox_Column-> setValue(1);
        QMessageBox::information (this, "Ошибка", "Количество колонок должно быть равно 1");
        return;

    }
//    int byte=0;
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как bin"),"C:\\Users\\student.GIS\\Downloads\\", tr("Binary files (*.bin)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Ошибка", "Файл не выбран");
    }
    else
    {
        QFileInfo fi = fileName;
        QString ext = fi.completeSuffix();
        if (ext != "bin")
        {
            QMessageBox::information(this, "Ошибка", "Неверный формат");
            return;
        }
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly);

        char *mas;
        int size_int = sizeof(int);
        mas = new char [size_int];

        int size = ui-> spinBox_Row-> value();
        memcpy (mas, &size, size_int);
        file.write (mas, size_int);




        for (int i = 0; i< size; i++)
        {
            if (ui->tableWidget-> item(i,0) == nullptr)
            {
                QTableWidgetItem * ti ;
                ti = new QTableWidgetItem;
                ui-> tableWidget-> setItem(i,0,ti);

            }
            bool flag;
            int tmp = ui-> tableWidget-> item(i,0)-> text().toInt(&flag);
            controlsum+=tmp;
            if (!flag)
            {
                tmp = 98989;
            }
            memcpy (mas, &tmp, size_int);
            file.write(mas, size_int);
//            byte += sizeof(mas);


        }
//        long long s = file.size();
        memcpy (mas, &controlsum, size_int);
        file.write(mas, size_int);
        file.close();
        delete [] mas;

    }
}

void MainWindow::on_pushButton_OpenBIN_clicked()
{
    QString fileName;
    int controlsum=0;
    fileName = QFileDialog::getOpenFileName(this, tr("Открыть bin"),"C:\\Users\\student.GIS\\Downloads\\", tr("Binary files (*.bin)"));
    if (fileName.isEmpty())
    {
        QMessageBox::information(this, "Ошибка", "Файл не выбран");
    }
    else
    {
        QFileInfo fi = fileName;
        QString ext = fi.completeSuffix();
        if (ext != "bin")
        {
            QMessageBox::information(this, "Ошибка", "Неверный формат");
            return;
        }
        QFile file;
        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);

        char *mas;
        int size_int = sizeof(int);
        mas = new char [size_int];

        int size = ui-> spinBox_Row-> value();

        file.read(mas,size_int);
        memcpy (&size,mas, size_int);


        if (file.size() != size_int*(size+2))
        {
            QMessageBox::information(this, "Ошибка", "Поврежденный файл");
        }
        else{
//            size-=1;
            ui-> spinBox_Row-> setValue(size);

            for (int i = 0; i< size; i++)
            {
                if (ui->tableWidget-> item(i,0) == nullptr)
                {
                    QTableWidgetItem * ti ;
                    ti = new QTableWidgetItem;
                    ui-> tableWidget-> setItem(i,0,ti);
                }
                int tmp;
                file.read(mas,size_int);


//                bool flag ;
//                QString numb = mas.toInt(&flag);
                memcpy (&tmp,mas, size_int);
                controlsum +=tmp;
                if (tmp == 98989)
                    ui-> tableWidget-> item(i,0) -> setText("Ошибка");
                else
                    ui-> tableWidget-> item(i,0) -> setText(QString::number(tmp));
            }
            file.read(mas,size_int);
            int sz;
             memcpy (&sz,mas, size_int);
            if (sz == controlsum)
            {
                 QMessageBox::information(this, "Ошибка", "Файл поврежден");
                 return;
            }

        }
        file.close();
        delete [] mas;
    }
}
