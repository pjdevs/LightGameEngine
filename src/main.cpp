// Copyright 2023 pjdevs. All rights reserved.
// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <entt/entt.hpp>
#include <linalg.h>

#include <LightGameEngine/Application.hpp>

using namespace linalg::aliases;

struct position
{
	float x;
	float y;
};

struct velocity
{
	float dx;
	float dy;
};

void update(entt::registry& registry)
{
	auto view = registry.view<const position, velocity>();

	// use a callback
	view.each([](const auto& pos, auto& vel) { std::cout << "Callback!\n"; });

	// use an extended callback
	view.each([](const auto entity, const auto& pos, auto& vel) { std::cout << "Extended callback!\n"; });

	// use a range-for
	for (auto [entity, pos, vel] : view.each())
	{
		std::cout << "Range-for!\n";
	}

	// use forward iterators and get only the components of interest
	for (auto entity : view)
	{
		auto& vel = view.get<velocity>(entity);
		std::cout << "Forward iterator and get!\n";
	}
}

float4 compute_plane(float3 a, float3 b, float3 c)
{
	float3 n = cross(b - a, c - a);
	return { n, -dot(n,a) };
}

int main()
{
	entt::registry registry;

	for (auto i = 0u; i < 10u; ++i)
	{
		const auto entity = registry.create();
		registry.emplace<position>(entity, i * 1.f, i * 1.f);
		if (i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
	}

	update(registry);

	compute_plane({ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 });

	Application().run();
}
