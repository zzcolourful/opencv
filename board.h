#ifndef BOARD_H
#define BOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPen>
#include <QVector>
#include <QPointF>
#include <QImage>

class Board : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth)
    Q_PROPERTY(QImage background READ background WRITE setBackground)
public:
    explicit Board(QQuickItem *parent = nullptr);
    QColor penColor() const;
    void setPenColor(const QColor &color);

    qreal penWidth() const;
    void setPenWidth(qreal width);

    QImage background()const;
    void setBackground(const QImage &image);


    void paint(QPainter *painter) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void clear();

private:
    QColor m_penColor;
    qreal m_penWidth;
    bool m_isDrawing;
    QPoint m_lastPoint;
    QVector<QLineF> m_lines;
    QImage m_background;

    void drawLine(const QPointF &start, const QPointF &end);


};

#endif // BOARD_H
