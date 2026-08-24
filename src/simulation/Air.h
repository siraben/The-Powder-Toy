#pragma once
#include "SimulationConfig.h"
#include <memory>

// Ambient heat scratch plane; see Air::ohv.
struct AirOhv
{
	float v[YCELLS][XCELLS];
};

class Simulation;
struct RenderableSimulation;

class Air
{
public:
	Simulation & sim;
	int airMode;
	float ambientAirTemp;
	float edgePressure;
	float edgeVelocityX;
	float edgeVelocityY;
	float vorticityCoeff;
	int convectionMode;
	// Ambient heat scratch; allocated on first use (see update_airh) so
	// sessions without ambient heat never pay for it.
	std::unique_ptr<AirOhv> ohv;
	float ovx[YCELLS][XCELLS];
	float ovy[YCELLS][XCELLS];
	float opv[YCELLS][XCELLS];
	float ocurl[YCELLS][XCELLS]; // Vorticity confinement scratch, valid only within update_air
	float ovortx[YCELLS][XCELLS]; // Vorticity confinement contributions, valid only within update_air
	float ovorty[YCELLS][XCELLS];
	unsigned char bmap_blockair[YCELLS][XCELLS];
	unsigned char bmap_blockairh[YCELLS][XCELLS];
	float kernel[9];
	void make_kernel(void);
	static float vorticity(const RenderableSimulation & sm, int y, int x);
	void update_airh(void);
	void update_air(void);
	void Clear();
	void ClearAirH();
	void Invert();
	void ApproximateBlockAirMaps(Rect<int> targetBlocks);
	Air(Simulation & sim);
};
