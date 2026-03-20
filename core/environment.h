#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "entity.h"

class Environment : public Entity
{
    Q_OBJECT
public:
    explicit Environment(QObject *parent = nullptr);

    //virtual
    bool passable() const override { return m_passable; }
    int id() const override {return m_id; }
    QPointF position() const override { return m_position; }

    void setPosition(const QPointF& pos) override;
    //virtual

private:
    int const m_id = 1;
    bool const m_passable = 0;
    QPointF m_position = QPointF(0, 0);
};

#endif // ENVIRONMENT_H
