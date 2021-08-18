#pragma once

#include <cstdint>
#include <algorithm>
#include <gsl/gsl>

struct Color {
  public:
	float R, G, B, A;
	constexpr Color(float R, float G, float B, float A = 1.f) noexcept;
	constexpr Color(int R, int G, int B, int A = 255) noexcept;

};

/*
     IMPLEMENTATION
*/
constexpr Color::Color(float R, float G, float B, float A = 1.f) noexcept : R {R}, G {G}, B {B}, A {A} {}
constexpr Color::Color(int R, int G, int B, int A) noexcept {
	R = static_cast<float>(gsl::narrow<uint8_t>(R)) / 255.f;
	G = static_cast<float>(gsl::narrow<uint8_t>(G)) / 255.f;
	B = static_cast<float>(gsl::narrow<uint8_t>(B)) / 255.f;
	A = static_cast<float>(gsl::narrow<uint8_t>(A)) / 255.f;
}

