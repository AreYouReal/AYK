#pragma once


namespace AYK {

	class Timestep {
	public:
		Timestep(float TimeToSet = 0.0f) : Time(TimeToSet) { }

		operator float() const { return(Time); }

		float GetSeconds() const { return(Time); }
		float GetMilliseconds() const { return(Time * 1000.0f); }

	private:
		float Time;
	};

}