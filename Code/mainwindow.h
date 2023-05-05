#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <opencv2/opencv.hpp>
#include <QMainWindow>
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
extern float index1;

extern int index2;

extern float index3;

extern int index4;

extern int index5;

extern int index6;

extern int index7;

extern int index8;

extern Mat src;

extern Mat src2;

extern Mat dst;

extern Mat resized_up;

extern int index9;

extern int index10;


//extern Mat resized_up2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_high_textHighlighted(const QString &arg1);

    void on_noise_textHighlighted(const QString &arg1);

    void on_low_textHighlighted(const QString &arg1);

    void on_add_g_editingFinished();

    void on_add_u_editingFinished();

    void on_add_s_editingFinished();

    void on_guasian_editingFinished();

    void on_mean_editingFinished();

    void on_median_editingFinished();

    void on_options_textHighlighted(const QString &arg1);

    void on_normalize_editingFinished();

    void on_manual_editingFinished();

    void on_local_editingFinished();

    void on_Histogram_textHighlighted(const QString &arg1);

//    void on_circle_t_sliderReleased();

//    void on_line_t_sliderReleased();


    void on_detection_textHighlighted(const QString &arg1);

    void on_Upload_clicked();


    void on_Upload_contour_clicked();

    void on_contour_clicked();

    void on_circle_t_editingFinished();

    void on_line_t_editingFinished();

    void on_upload_harris_clicked();

    void on_Harris_clicked();

    void on_upload_img_clicked();

    void on_upload_temp_clicked();

    void on_match_textHighlighted(const QString &arg1);

    void on_NCC_editingFinished();

    void on_SSD_editingFinished();

    void on_sift_clicked();


    void on_Segm_textHighlighted(const QString &arg1);

    void on_upload_seg_clicked();

    void on_Kmean_editingFinished();

    void on_upload_threshold_clicked();

    void on_threshold_textHighlighted(const QString &arg1);

    void on_mean_shift_clicked();

    void on_itterative_local_editingFinished();

    void on_otsu_editingFinished();

    void on_gray_clicked();

    void on_coloredReigion_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
