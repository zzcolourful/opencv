#include "Board.h"
#include <QQuickItem>




Board::Board(QQuickItem *parent) :QQuickPaintedItem(parent),
    m_penColor(Qt::black),
    m_penWidth(2),
    m_isDrawing(false)
{
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);


}

QColor Board::penColor() const
{
    return m_penColor;
}

void Board::setPenColor(const QColor &color)
{
    m_penColor = color;
    update();

}

qreal Board::penWidth() const
{
    return m_penWidth;
}

void Board::setPenWidth(qreal width)
{
    m_penWidth = width;
    update();

}

QImage Board::background() const
{
    return m_background;

}

void Board::setBackground(const QImage &image)
{
    m_background = image;
    update();

}

void Board::paint(QPainter *painter)
{
    //    painter->setPen(QPen(m_penColor, m_penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //    for (const QLineF &line : qAsConst(m_lines))
    //        painter->drawLine(line);
    if(!m_background.isNull()){
        QSize size = boundingRect().size().toSize();
        painter->drawImage(QPoint(0,0),m_background.scaled(size,Qt::KeepAspectRatio));

    }
    for (const QLineF &line : qAsConst(m_lines))
        painter->drawLine(line);
}

void Board::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_lastPoint = event->pos();
    }
    if(event->button() == Qt::RightButton){
        clear();
    }
}

void Board::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDrawing) {
        drawLine(m_lastPoint, event->pos());
        m_lastPoint = event->pos();
    }
}

void Board::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = false;
    }
}

void Board::clear()
{
    m_lines.clear();
    update();

}

void Board::drawLine(const QPointF &start, const QPointF &end)
{
    m_lines.append(QLineF(start, end));
    update();
}


