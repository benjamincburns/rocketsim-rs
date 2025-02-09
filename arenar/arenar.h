#pragma once

#include "RocketSim.h"

const CarConfig& getOctane();
const CarConfig& getDominus();
const CarConfig& getPlank();
const CarConfig& getBreakout();
const CarConfig& getHybrid();
const CarConfig& getMerc();

struct EBoostPadState {
	bool isActive;
	float cooldown;
	uint32_t curLockedCarId = 0;
	uint32_t prevLockedCarID = 0;
};

struct Arenar {
    Arena* a;

    Arenar(GameMode game_mode, float tick_rate = 120) {
        a = Arena::Create(game_mode, tick_rate);
    }

    ~Arenar() {
        delete a;
    }

    // No copy constructor
    Arenar(const Arenar & other) = delete;
    Arenar & operator =(const Arenar & other) = delete;

    // Move constructor
    Arenar(Arenar&& other) = default;
    Arenar& operator =(Arenar && other) = default;

	// extra car stuff
	size_t num_cars() const {
		return a->_cars.size();
	}

	uint32_t get_car_id(size_t index) const {
		return a->_cars[index]->id;
	}

	std::unique_ptr<std::vector<CarState>> GetCars();
	CarState GetCar(uint32_t car_id);
	/// @brief Sets the state of a car in the arena
	/// @param arena
	/// @param state
	/// @param carID
	/// @return True if the car was found and the state was set, false otherwise
	bool SetCar(uint32_t car_id, const CarState state);

	uint32_t AddCar(Team team, const CarConfig& config) {
		return a->AddCar(team, config)->id;
	}

	bool RemoveCar(uint32_t car_id);
	/// @brief Sets the controls of a car for the next tick
	/// @param arena
	/// @param state
	/// @param carID
	/// @return True if the car was found and the state was set, false otherwise
	bool SetCarControls(uint32_t car_id, const CarControls controls);
	bool DemolishCar(uint32_t car_id);
	bool RespawnCar(uint32_t car_id, int32_t seed);

	// extra ball stuff

	BallState GetBall() const {
		return a->ball->GetState();
	}

	void SetBall(const BallState& state) {
		a->ball->SetState(state);
	}

	// boost pad stuff

	size_t num_pads() const {
		return a->_boostPads.size();
	}

	bool get_pad_is_big(size_t index) const;
	Vec GetPadPos(size_t index) const;
	void SetPadState(size_t index, const EBoostPadState& state);
	EBoostPadState GetPadState(size_t index) const;

	// extra misc stuff

	uint64_t get_tick_count() const {
		return a->tickCount;
	}

	float get_tick_rate() const {
		return 1 / a->tickTime;
	}

	void ResetToRandomKickoff(int32 seed = -1) {
		a->ResetToRandomKickoff(seed);
	}

	void step(int32 ticks = 1) {
		a->Step(ticks);
	}
};
