#include <string>
#include "Mode.hpp"
#include "Text.hpp"



struct StoryMode : Mode {
	StoryMode();
	virtual ~StoryMode();
	int pure_text = 0;
	int cool = 0;
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//called to create menu for current scene:
	void enter_scene();

	enum {
		Opening,
		Apartment,
		LeavingApartment,
		CrowdStreet,
		WalkOrApproach,
		Supermarket, 
		LeavingSupermarket,
		GoingBack,
		LeavingStreet,
		EndingTwo,
		EndingThree,
		CreditsOne,
		CreditsTwo,
		CreditsThree
	} states = Opening;
	
	struct {
		bool first_choice = true;
		bool searched_bed = false;
		bool searched_desk = false;
		bool failed_search = false;
		bool found_in_bed = true;
	} apartment_search;

	struct {
		bool first_choice = true;
		bool clean_clothes = false;
		bool remove_clothes_choice = false;
		bool tried_shower = false;
		bool tried_leave = false;
		int leave_dirty = 1;
	} apartment_leave;

	struct {
		bool first_choice = true;
		bool continue_walking = false;
		bool approach_crowd = false;
		int approach_number = 1;
	} crowded_street;

	struct {
		bool first_choice = true;
		bool next_page = false;
		bool flipped_pages = false;
		int attempt_number = 1;
		bool got_matches = false;
	} supermarket;

	struct {
		bool first_choice = true;
		bool tried_examine = false;
		bool examined_post_no_matches = false;
		bool examined_post_matches = false;
		bool tried_supermarket = false;
	} empty_street;


	glm::vec2 view_min = glm::vec2(0,0);
	glm::vec2 view_max = glm::vec2(1000, 1000);
};
