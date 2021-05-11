include "system.hpp"

void System::initialize()
{

	for (int i = 0; i < 5; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (k - 1 >= 0)
			{
				m_links.push_back(Link(particle(i * 10 + k), particle(i  * 10 + k - 1), 0.5f));
			}
			if (i - 1 >= 0 && k - 1 >= 0)
			{
				m_links.push_back(Link(particle(i * 10 + k), particle((i - 1) * 10 + k - 1), 0.5f));
			}
			if (i - 1 >= 0)
			{
				m_links.push_back(Link(particle(i * 10 + k), particle((i - 1) * 10 + k), 0.5f));
			}
			if (i - 1 >= 0 && k + 1 < 10)
			{
				m_links.push_back(Link(particle(i * 10 + k), particle((i - 1) * 10 + k + 1), 0.5f));
			}

			


		}
	}


}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(0.25f);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}

	
}
