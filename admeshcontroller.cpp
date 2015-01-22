#include "admeshcontroller.h"
#include <QFileDialog>
#include <QtWidgets>
#include <string>
//#include <QVector3D>

using namespace std;

admeshController::admeshController(QObject *parent) :
    QObject(parent)
{
    stl = NULL;
    active = NULL;
    m_scale = 1.0;
    x_rot = 0.0;
    y_rot = 0.0;
    z_rot = 0.0;
    x_translate = 0.0;
    y_translate = 0.0;
    z_translate = 0.0;
    rel_translate = true;
    fixall_flag = false;
    exact_flag = false;
    tolerance_flag = false;
    tolerance = 0.0;
    increment_flag = false;
    increment = 0.0;
    nearby_flag = false;
    iterations = 1;
    remove_unconnected_flag = false;
    fill_holes_flag = false;
    normal_directions_flag = false;
    normal_values_flag = false;
    reverse_all_flag = false;
}

admeshController::~admeshController()
{
    delete stl;
    active = NULL;
}

void admeshController::drawAll(QGLShaderProgram *program)
{
     program->setUniformValue("color", color);
     program->setUniformValue("badColor", badColor);
     if(stl) stl->drawGeometry(program);
}

void admeshController::setDrawColor(QVector3D col, QVector3D badCol){
    color = col;
    badColor = badCol;
}

char* QStringToChar(QString str)
{
    string s = str.toStdString();
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

void admeshController::openSTL()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, _("Open STL"), "/", _("STL (*.stl)"));
    if(!fileName.isEmpty()){
        MeshObject* tmp = new MeshObject;
        char *file = QStringToChar(fileName);
        if(!tmp->loadGeometry(file)){
            QString msg;
            QTextStream(&msg) << _("File ") << fileName << _(" could not be opened.\n");
            QMessageBox::critical(NULL, _("Error"), msg);
        }else{
            stl = tmp;
            active = stl;
        }
        delete []file;
    }
    reDrawSignal();
}

void admeshController::openSTLbyName(const char* filename)
{
    char* file = const_cast<char *>(filename);
    MeshObject* tmp = new MeshObject;
    if(!tmp->loadGeometry(file)){
        QString msg;
        QTextStream(&msg) << _("File ") << file << _(" could not be opened.\n");
        QMessageBox::critical(NULL, _("Error"), msg);
    }else{
        stl = tmp;
        active = stl;
    }
    reDrawSignal();
}

void admeshController::setScale(double param)
{
    m_scale = (float)param;
}

void admeshController::scale()
{
    if(active) active->scale(m_scale);
}

void admeshController::mirrorXY()
{
    if(active) active->mirrorXY();
}

void admeshController::mirrorYZ()
{
    if(active) active->mirrorYZ();
}

void admeshController::mirrorXZ()
{
    if(active) active->mirrorXZ();
}

void admeshController::setXRot(double angle)
{
    x_rot = (float)angle;
}

void admeshController::setYRot(double angle)
{
    y_rot = (float)angle;
}

void admeshController::setZRot(double angle)
{
    z_rot = (float)angle;
}

void admeshController::rotateX()
{
    if(active) active->rotateX(x_rot);
}

void admeshController::rotateY()
{
    if(active) active->rotateY(y_rot);
}

void admeshController::rotateZ()
{
    if(active) active->rotateZ(z_rot);
}

void admeshController::setXTranslate(double factor)
{
    x_translate = factor;
}

void admeshController::setYTranslate(double factor)
{
    y_translate = factor;
}

void admeshController::setZTranslate(double factor)
{
    z_translate = factor;
}

void admeshController::setRelativeTranslate()
{
    if(rel_translate) rel_translate = false;
    else rel_translate = true;
}

void admeshController::translate()
{
    if(active) active->translate(rel_translate, x_translate, y_translate, z_translate);
}


void admeshController::setFixAllFlag()
{
    fixall_flag = !fixall_flag;
}

void admeshController::setExactFlag()
{
    exact_flag = !exact_flag;
}

void admeshController::setToleranceFlag()
{
    tolerance_flag = !tolerance_flag;
}

void admeshController::setTolerance(double val)
{
    tolerance = val;
}

void admeshController::setIncrementFlag()
{
    increment_flag = !increment_flag;
}

void admeshController::setIncrement(double val)
{
    increment = val;
}

void admeshController::setNearbyFlag()
{
    nearby_flag = !nearby_flag;
}

void admeshController::setIterations(int val)
{
    iterations = val;
}

void admeshController::setRemoveUnconnectedFlag()
{
    remove_unconnected_flag = !remove_unconnected_flag;
}

void admeshController::setFillHolesFlag()
{
    fill_holes_flag = !fill_holes_flag;
}

void admeshController::setNormalDirFlag()
{
    normal_directions_flag = !normal_directions_flag;
}

void admeshController::setNormalValFlag()
{
    normal_values_flag = !normal_values_flag;
}

void admeshController::setReverseAllFlag()
{
    reverse_all_flag = !reverse_all_flag;
}
