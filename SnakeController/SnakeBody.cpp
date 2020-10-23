#include "SnakeBody.hpp"
#include <algorithm>
#include <sstream>
#include "EventT.hpp"
#include "IPort.hpp"

bool SnakeBody::isSegmentAtPosition(int x, int y) const
{
    return m_segments.end() !=  std::find_if(m_segments.cbegin(), m_segments.cend(),
        [x, y](auto const& segment){ return segment.x == x and segment.y == y; });
}

namespace
{
    bool isHorizontal(Direction direction)
    {
        return Direction_LEFT == direction or Direction_RIGHT == direction;
    }

    bool isVertical(Direction direction)
    {
        return Direction_UP == direction or Direction_DOWN == direction;
    }

    bool isPositive(Direction direction)
    {
        return (isVertical(direction) and Direction_DOWN == direction)
            or (isHorizontal(direction) and Direction_RIGHT == direction);
    }

    bool perpendicular(Direction dir1, Direction dir2)
    {
        return isHorizontal(dir1) == isVertical(dir2);
    }
}

SnakeBody::Segment SnakeBody::calculateNewHead() const
{
    Segment const& currentHead = m_segments.front();

    Segment newHead;
    newHead.x = currentHead.x + (isHorizontal(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);
    newHead.y = currentHead.y + (isVertical(m_currentDirection) ? isPositive(m_currentDirection) ? 1 : -1 : 0);

    return newHead;
}

void SnakeBody::removeTailSegment()
{
    auto tail = m_segments.back();

    DisplayInd l_evt;
    l_evt.x = tail.x;
    l_evt.y = tail.y;
    l_evt.value = Cell_FREE;
    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(l_evt));

    m_segments.pop_back();
}

void SnakeBody::addHeadSegment(Segment const& newHead)
{
    m_segments.push_front(newHead);

    DisplayInd placeNewHead;
    placeNewHead.x = newHead.x;
    placeNewHead.y = newHead.y;
    placeNewHead.value = Cell_SNAKE;

    m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewHead));
}



