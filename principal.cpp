#include "principal.h"
#include "ui_principal.h"

#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instancia del objeto imagen
    m_imagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    //Rellenar de blanco
    m_imagen->fill(Qt::white);
    // Instancias el objeto painter
    m_painter = new QPainter(m_imagen);
    // Instanciar el ancho
    m_ancho = DEFAULT_ANCHO;

}

Principal::~Principal()
{
    delete ui;

}
void Principal::paintEvent(QPaintEvent *event)
{
    //Pantalla en blanco
    // Crear otro painter (local)
    QPainter painter(this);
    //Dibujar la imagen
    painter.drawImage(0,0, *m_imagen);
    // Aceptar el evento
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    if(m_opcion == 1){
            m_ptInicial = event->pos();
        }else if(m_opcion == 2){
            if(m_toogle){
                m_ptInicial = event->pos();
            }else{
                m_ptFinal = event->pos();
                QPen pincel;
                pincel.setWidth(m_ancho);
                pincel.setColor(m_color);
                m_painter->setPen(pincel);
                m_painter->drawLine(m_ptInicial, m_ptFinal);
                // Redibujar la interfaz gráfica
                update();
            }
        }else if(m_opcion == 3){
            if(m_toogle){
                m_ptInicial = event->pos();
            }else{
                m_ptFinal = event->pos();
                // Dibujar rectangulo
                int ancho = m_ptFinal.x() - m_ptInicial.x();
                int alto = m_ptFinal.y() - m_ptInicial.y();
                QPen pincel;
                pincel.setWidth(m_ancho); // Modificar el ancho seleccionado
                pincel.setColor(m_color); // Modificar el color seleccionado
                m_painter->setPen(pincel);
                m_painter->drawRect(m_ptInicial.x(),
                                    m_ptInicial.y(),
                                    ancho, alto);
                // Redibujar la interfaz gráfica
                update();
            }
        }else if(m_opcion == 4){
            if(m_toogle){
                m_ptInicial = event->pos();
            }else{
                m_ptFinal = event->pos();
                //Circunferencia
                QPen pincel;
                pincel.setWidth(m_ancho); // Modificar el ancho seleccionado
                pincel.setColor(m_color); // Modificar el color seleccionado
                m_painter->setPen(pincel);
                QRectF circulo(m_ptInicial, m_ptFinal);
                m_painter->drawEllipse(circulo);
                // Redibujar la interfaz gráfica
                update();
            }
        }
        m_toogle = !m_toogle;
}


void Principal::mouseMoveEvent(QMouseEvent *event)
{
    m_ptFinal = event->pos();
    // Crear pincel
    QPen pincel;
    pincel.setColor(m_color);
    m_painter->setPen(pincel);
    pincel.setWidth(m_ancho);
    m_painter->drawLine(m_ptInicial, m_ptFinal);
    // Redibujar la interfaz grafica
    update();
    m_ptInicial = m_ptFinal;
}

void Principal::on_actionNuevo_triggered()
{
    m_imagen->fill(Qt::white);
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QDir directorio=QDir::home();
    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar imagen",QString(),"Imagenes (*.png)");

        if (!nombreArchivo.isEmpty() ){
            if (m_imagen->save(nombreArchivo))
                QMessageBox::information(this,"Guardar imagen","Archivo almacenado en: " + nombreArchivo);
            else
                QMessageBox::warning(this,"Guardar imagen", "No se puede guardar la imagen");
        }
}


void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionLibre_triggered()
{
    m_opcion = 1;
}

void Principal::on_actionLineas_triggered()
{
    m_opcion = 2;
}

void Principal::on_actionColor_triggered()
{
    m_color = QColorDialog::getColor(Qt::white,this);
}

void Principal::on_actionRect_ngulos_triggered()
{
    m_opcion = 3;
}

void Principal::on_actionCircunferencias_triggered()
{
    m_opcion = 4;
}
