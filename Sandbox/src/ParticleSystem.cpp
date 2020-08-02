#include "ParticleSystem.h"

#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include <random>

class Random {

public:

	static void Init() {
		//RandomEngine.seed(std::random_device());
	}

	static float Float() {
		return((float)Distribution(RandomEngine) / (float)std::numeric_limits<uint32_t>::max());
	}

private:
	static std::random_device RndDevice;
	static std::mt19937 RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> Distribution;

};

std::random_device Random::RndDevice;
std::mt19937 Random::RandomEngine(RndDevice());
std::uniform_int_distribution<std::mt19937::result_type> Random::Distribution;


ParticleSystem::ParticleSystem(uint32_t MaxParticles) :m_PoolIndex(MaxParticles - 1) {
	m_ParticlePool.resize(MaxParticles);
}

void ParticleSystem::OnUpdate(AYK::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position += particle.Velocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void ParticleSystem::OnRender(AYK::OrthographicCamera& camera)
{
	
	AYK::Renderer2D::BeginScene(camera);

	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		//color.a = color.a * life;

		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);
		glm::vec3 Pos = glm::vec3(particle.Position.x, particle.Position.y, 0.2f);
		AYK::Renderer2D::DrawRotatedQuad(Pos, {size, size}, particle.Rotation, color);

	}

	AYK::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}