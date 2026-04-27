#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "entity.h"

class Environment : public Entity
{
    Q_OBJECT
public:
    explicit Environment(QObject *parent = nullptr);
    ~Environment() {};

    //virtual
    bool passable() const override { return m_passable; }
    int id() const override {return m_id; }
    QPointF position() const override { return m_position; }
    qreal width() const override {return m_width; }
    qreal height() const override {return m_height; }
    QRectF hitbox() const override {return m_hitbox; }

    void setPosition(const QPointF& pos) override;
    //virtual

private:
    int const m_id = 1;
    bool const m_passable = 0;
    QPointF m_position = QPointF(0, 0);
    qreal m_height = 40;
    qreal m_width = 40;
    QRectF m_hitbox = QRectF(m_position.x(), m_position.y(), width(), height());
};

#endif // ENVIRONMENT_H
