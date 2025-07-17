#pragma once

class Competitor {

public:

	int competitors_id;
	int completed_task;
	int time;
	int score;
	int attempts;

	Competitor(int id, int completed, int timeSpent, int score, int attempts) : competitors_id(id), completed_task(completed), time(timeSpent), score(score), attempts(attempts)
	{

	}

	bool operator<(const Competitor& other) const { return compare(other) < 0; }
	bool operator<=(const Competitor& other) const { return compare(other) <= 0; }
	bool operator>(const Competitor& other) const { return compare(other) > 0; }
	bool operator>=(const Competitor& other) const { return compare(other) >= 0; }
	bool operator==(const Competitor& other) const { return compare(other) == 0; }
	bool operator!=(const Competitor& other) const { return compare(other) != 0; }

private:
	int compare(const Competitor& other) const {
		if (score != other.score) return score - other.score;
		if (time != other.time) return other.time - time;
		if (completed_task != other.completed_task) return completed_task - other.completed_task;
		if (attempts != other.attempts) return other.attempts - attempts;
		return other.competitors_id - competitors_id;
	}
};
