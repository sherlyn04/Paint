#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMouseEvent>
#include <QMainWindow>
#include <QImage>
#include <QDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QAbstractButton>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QDir>

#define DEFAULT_ANCHO 4

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionSalir_triggered();

    void on_actionLibre_triggered();

    void on_actionLineas_triggered();

    void on_actionColor_triggered();

    void on_actionRect_ngulos_triggered();

    void on_actionCircunferencias_triggered();

private:
    Ui::Principal *ui;
    QImage *m_imagen;       // Imagen sobre la cual se va a dibujar
    QPainter *m_painter;    // El objeto painter
    QPoint m_ptInicial;     // Punto incial para dibujar
    QPoint m_ptFinal;       // Punto final para dibujar
    QColor m_color;         // Colores
    int m_opcion;
    int m_ancho;
    bool m_toogle = true;
};
#endif // PRINCIPAL_H
