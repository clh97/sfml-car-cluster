#include "semi_meter.hpp"
#include "effects/interpolate.hpp"

void SemiMeter::update(sf::Time deltaTime)
{
    m_ticks.clear();
    // m_ticks.reserve((int)max - (int)min);

    int iteration = 0;
    for (int i = (int)min; i <= max; i += max >= 1000 ? 1000 : 10)
    {
        float value = (float)i;
        float angle = 90.0f - (value - min) / (max - min) * 180.f;
        bool odd = iteration % 2;
        float tickLength = odd ? this->dialRadius * 0.1f : this->dialRadius * 0.05f;
        float tickWidth = odd ? 2.5f : 1.f;
        sf::Color tickColor = odd ? sf::Color::Red : sf::Color::White;

        sf::RectangleShape line(sf::Vector2f(2.f, tickLength));
        line.setOrigin(1.f, this->dialRadius * 0.9f);
        line.setFillColor(tickColor);
        line.setOutlineColor(tickColor);
        line.setOutlineThickness(tickWidth);
        line.setRotation(angle);
        line.setPosition(this->position.x, this->position.y);

        m_ticks.push_back(line);
        iteration++;
    }
}

void SemiMeter::setValue(float value)
{
    this->value = value;
    int angle = (value - min) / (max - min) * 180.f;
    int rotation = m_needle.getRotation();
    float interpolatedAngle = Interpolate::sinusoidalInterpolate(rotation, angle, 0.1f);
    m_needle.setRotation(interpolatedAngle);

    if (value > this->max * 0.8f)
    {
        m_needle.setFillColor(sf::Color::Red);
    }
    else
    {
        m_needle.setFillColor(sf::Color::Green);
    }
}

void SemiMeter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_dial);
    for (const auto &tick : m_ticks)
    {
        target.draw(tick);
    }
    target.draw(m_needle);
    target.draw(m_needle_center);
}

SemiMeter::SemiMeter(const sf::Vector2f &position,
                     const sf::Vector2f &size, float min, float max, std::string textSuffix)
    : m_dial(), m_needle_center(), m_needle(), m_text(), min(min), max(max), dialRadius(size.x), textSuffix(textSuffix), position(position), size(size)
{
    value = min;

    const float num_points = 50;
    const float start_angle = PI / 2.f;
    const float end_angle = (2.f * PI - start_angle);
    const float angle_step = (end_angle - start_angle) / num_points;
    const float outer_radius = this->dialRadius;

    m_dial = sf::VertexArray(sf::LinesStrip, num_points);

    for (int i = 0; i <= num_points; ++i)
    {
        float angle = (i * angle_step) * -1;
        float x = position.x + cos(angle) * outer_radius;
        float y = position.y + sin(angle) * outer_radius;

        m_dial[i] = sf::Vertex(sf::Vector2f(x, y));
    }

    // m_dial = sf::CircleShape(this->dialRadius, this->dialRadius / 2);
    // m_dial.setRadius(this->dialRadius);
    // m_dial.setFillColor(sf::Color::Transparent);
    // m_dial.setOutlineColor(sf::Color(255, 255, 255, 50));
    // m_dial.setOutlineThickness(2.f);
    // m_dial.setOrigin(this->dialRadius, this->dialRadius);
    // m_dial.setPosition(position.x + size.x / 2, position.y + size.y / 2);
    // m_dial.setRotation(90.f);

    m_needle.setSize(sf::Vector2f(needleLength, 6.f));
    m_needle.setFillColor(sf::Color::Red);
    m_needle.setOrigin(needleLength, 0.0f);
    m_needle.setPosition(position.x, position.y);
    m_needle.setRotation(90.f);

    m_needle_center.setRadius(this->dialRadius * 0.2f);
    m_needle_center.setFillColor(sf::Color::Black);
    // m_needle_center.setOutlineColor(sf::Color::White);
    // m_needle_center.setOutlineThickness(2.f);
    m_needle_center.setOrigin(this->dialRadius * 0.25f, this->dialRadius * 0.25f);
    m_needle_center.setPosition(position.x, position.y);

    this->update(sf::Time::Zero);
}
