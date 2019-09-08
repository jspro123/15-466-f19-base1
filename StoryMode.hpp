#include <string>
#include "Mode.hpp"


struct Sentence {

	std::string text;
	float wait_to_print = 1.0f; //Didn't really use this, but you never know
	//A drawing speed entry would have been cool and very little effor, but I 
	//wouldn't have used it either.

	Sentence(std::string const text_, float wait_to_print_ = 1.0f) {
		text = text_;
		wait_to_print = wait_to_print_;
	}
};


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

	//SPOILERS BELOW (lol)
	/* -------------- INTRODUCTION --------------*/

	std::string const openingText1 = "A low, piercing ring fills the room. "
		"The sound wakes you up, annoyed and tired. ";
	
	std::string const openingText2 = "What the - , you think as you reach for your phone, the source of your disturbance. "
		"Before you can open it, though, the sound stops and the notification vanishes. "
		"You stare blankly at the screen for a bit before turning it on. 23:30. Hm. "
		"Now's as good of a time as any. You rub your eyes and stretch before getting up. ";

	std::string const returnKey = "Press enter to continue . . . ";
	std::string const exitKey = "Press enter to exit the game . . . ";

	/* -------------- FINDING THE GROCERRY LIST --------------*/

	std::string const apartmentIntro = "Your apartment's seen better days and better renters. "
		"It stands quite bare, save for a few necessities; TV, fridge, a bed, and some desks "
		"are all that's there. You're not the cleanest, either; stains are splattered all "
		"across the carpet. And the smell - was it always this bad? You look around, searching "
		"for your grocery list. ";
	std::string const apartmentIntroAbridged = "Where did you put it? You keep looking.";

	std::string const apartmentIntroChoice1 = "Check near the bed";
	std::string const apartmentIntroSearchBed1 = "You look all around the nightstand, but find nothing. "
		"Well, that's not entirely true - you find your wallet, carelessly thrown on the floor.";
	std::string const apartmentIntroChoice2 = "Check around the desk";
	std::string const apartmentIntroSearchDesk1 = "You look all around the desk, but find nothing. "
		"Well, that's not entirely true - you find your wallet, carelessly thrown on the floor.";
	std::string const apartmentIntroSearchFailure = "You find nothing else. ";
	std::string const apartmentIntroSearchDesk2 = "You find the paper under a paperweight and grab it.";
	std::string const apartmentIntroSearchBed2 = "You spot the paper near the edge of the nightstand and grab it. ";

	/* -------------- PREPARING TO LEAVE --------------*/

	std::string const apartmentReadingList = "You look at the list : bleach, cheese, pasta, some meat - right, "
		"you had to empty the fridge the other day; some food would be nice. The supermarket's not far; "
		"you start getting ready to head out. ";
	std::string const apartmentReadingListAbridged = "Time to change and head out.";
	std::string const apartmentReadingListUAbridged = "Time to head out.";
	std::string const apartmentReadingListChoice1 = "Change clothes ";
	std::string const apartmentReadingListChange1 = "You take off the filth that you were wearing and put on some clean clothes. ";
	std::string const apartmentReadingListChoice2 = "Take a shower ";
	std::string const apartmentReadingListShower1 = "The shop will close soon. You should shower later. ";
	std::string const apartmentReadingListChoice3 = "Walk outside";
	std::string const apartmentReadingListLeaveYes = "You open the door and head out. ";
	std::string const apartmentReadingListLeaveNo1 = "You look and smell terrible. Perhaps you should change. ";
	std::string const apartmentReadingListLeaveNo2 = "You'd rather not offend the senses of those around you.";
	std::string const apartmentReadingListLeaveNo3 = "You'd rather not . . . ";
	std::string const apartmentReadingListLeaveNo4 = "Maybe . . .";
	std::string const apartmentReadingListLeaveNo5 = "Maybe . . .";
	std::string const apartmentReadingListLeaveNo6 = "Maybe . . . it's for the best . . . ";
	std::string const apartmentReadingListLeaveNo7 = "You take a deep breath and head out. ";

	/* -------------- CROWDED STREET --------------*/

	std::string const streetCrowdedIntro = "On your way there, you spot a crowd gathering around a broken lamppost in the distance. "
		"It's too dark for you to see what they're doing or hear what they're saying, "
		"but you can make out the sounds of someone crying. ";

	std::string const streetCrowdedIntroAbridged = "You continue watching the crowd, motionless. ";
	std::string const streetCrowdedChoice1 = "Approach the crowd";
	std::string const streetCrowdedApproach1 = "The supermarket will close soon. Wasting time here might cost you.";
	std::string const streetCrowdedApproach2 = "Could that crowd be - you hesitate. You would rather not know. You should continue on your way.";
	std::string const streetCrowdedApproach3 = "You shake your head. No, you would rather know. You start walking towards the crowd. ";
	std::string const streetCrowdedApproachDirty = "Almost as if sensing your intentions, the crowd disperses. Suddenly, however, you're blinded "
		"by a bright light; someone's pointed a flashlight towards you. The sounds of screams fill the air, "
		"and you feel your ribs cracking as you are suddenly tackled to the ground. Your head slams against "
		"the street, and everything goes dark. ";
	std::string const streetCrowdedApproachClean = "Almost as if sensing your intentions, the crowd disperses. You spot, however, "
		"the figure of the crying women, as she steps back into one of the houses. "
		"Very quickly, you're left alone on the street. You look at the lamppost "
		"where the crowd was centered, but it's too dark to see anything - and you're "
		"not willing to move any closer. You start walking back to the supermarket. ";
	std::string const streetCrowdedChoice2 = "Continue walking";
	std::string const streetCrowdedWalk1 = "You ignore the crowd and continue on your way. ";

	/* -------------- SUPERMARKET --------------*/

	std::string const supermarketIntro = "You step inside. It's obvious that you've arrived just in time; "
		"the clerk is busy getting ready to close for the night. He looks up. "
		"You immediately conclude that, as expected, he's been drinking all night. ";
	std::string const supermarketClean = "\"Hel-hel-hi the-re\", he stammers, \"We're . . .\" "
		"You ignore him and begin crossing out the items on your list. ";
	std::string const supermarketDirty = "\"Hel-hel-hi the-re\", he stammers, \"Nic-e shirt\". You stop, "
		"annoyed that he noticed despite his usual stupor. You look around "
		"to double-check that there are no cameras, and begin crossing out the items on your list.";
	std::string const supermarketForget = "As you're about to leave, though, you stop. Aren't you forgetting something? "
		"You think for a moment. Yes, you're definitely forgetting something; something "
		"that you didn't need when you wrote the list. But what . . . ?";

	std::string const supermarketCorrect = "Matches";
	std::string const supermarketBad1 = "Gloves";
	std::string const supermarketBad2 = "Screwdriver";
	std::string const supermarketBad3 = "Shoelaces";
	std::string const supermarketBad4 = "Tape";
	std::string const supermarketBad5 = "Jerky";
	std::string const supermarketNext = "Next";
	std::string const supermarketPrevious = "Previous";
	std::string const supermarketThinking = "You pause and try and to remember what it was that you needed.";
	std::string const supermarketWrongGuess1 = "No, that wasn't it.";
	std::string const supermarketWrongGuess2 = "No, that wasn't it either. Forget it, you think. Whatever it was can wait. You grab your bags and head out. ";
	std::string const supermarketRightGuess = "Yes, that's what you needed. You buy a box of matches along with your things and head out.";

	/* -------------- STREET AGAIN --------------*/

	std::string const streetIgnoredCrowd = "As you walk back, you notice that the crowd is still there. You shrug and continue moving.";
	std::string const streetApproachedCrowd = "You quickly reach the street where the crowd was gathered. You see nothing of note, "
												"save for the lamppost where they were standing.";
	std::string const streetApproachedCrowdAbridged = "You stare at the lamppost, uncertain. ";
	std::string const streetChoice1 = "Continue walking home";
	std::string const streetWalkHome1 = "You shrug and continue on your way.";
	std::string const streetChoice2 = "Examine the lamppost" ;
	std::string const streetExamine1 = "You look around hesitantly and step towards the lamppost. Now that you're up close, you think "
		"you see something stuck to it, but it's too dark to tell. ";
	std::string const streetExamine2 = "It's too dark to see what it is, and you're not getting any closer. ";
	std::string const streetExamineMatch = "You strike a match and bring it towards the lamppost.  You see a poster taped on, a girl's "
		"smiling face prominently in the center. You say nothing as you shake the matchstick and walk away. Now you know. ";
	std::string const streetChoice3 = "Walk back to the supermarket";
	std::string const streetWalkSupermarket1 = "You check the time and sigh. Too late. ";

	/* -------------- BACK IN APARTMENT --------------*/

	std::string const endingTwo1 = "Phew, you think as you lock the door, glad that's done with. You set your bags next to the fridge and relax "
		"on the bed. You look around the apartment and shake your head - perhaps it could use some cleaning. Especially the carpet. ";
	std::string const endingTwo2 = "You stand up and get to work. ";
	std::string const endingThree1 = "You make sure no one followed you as you lock the door behind you. Now was not the time to be careless. You sit "
		"on the bed as you ponder your next step. You need to be thorough . . . yes that's it. Erase everything. Might as well start now. ";
	std::string const endingThree2 = "You pick up the bleach. You open the fridge door. The stench of death is overpowering. ";

	std::string const creditsOne = "Hint: Perhaps something about you caught the crowd's attention . . . ";
	std::string const creditsTwo = "Another day goes by . . .";
	std::string const creditsThree = "Inspired by Shade and 9:05.";


	/* ----------------------- SENTENCES ----------------------- */
	/* --------------------------------------------------------- */


	/* -------------- INTRODUCTION --------------*/

	Sentence opening_text_1 = Sentence(openingText1);
	Sentence opening_text_2 = Sentence(openingText2);
	Sentence return_key = Sentence(returnKey);
	Sentence exit_key = Sentence(exitKey);

	/* -------------- FINDING THE GROCERRY LIST --------------*/

	Sentence apartment_intro = Sentence(apartmentIntro);
	Sentence apartment_intro_abridged = Sentence(apartmentIntroAbridged);
	Sentence apartment_intro_choice_1 = Sentence(apartmentIntroChoice1);
	Sentence apartment_intro_choice_search_bed_1 = Sentence(apartmentIntroSearchBed1);
	Sentence apartment_intro_choice_2 = Sentence(apartmentIntroChoice2);
	Sentence apartment_intro_choice_search_desk_1 = Sentence(apartmentIntroSearchDesk1);
	Sentence apartment_intro_search_failure = Sentence(apartmentIntroSearchFailure);
	Sentence apartment_intro_choice_search_bed_2 = Sentence(apartmentIntroSearchBed2);
	Sentence apartment_intro_choice_search_desk_2 = Sentence(apartmentIntroSearchDesk2);

	/* -------------- PREPARING TO LEAVE --------------*/

	Sentence apartment_reading_list = Sentence(apartmentReadingList);
	Sentence apartment_reading_list_abridged = Sentence(apartmentReadingListAbridged);
	Sentence apartment_reading_list_u_abridged = Sentence(apartmentReadingListUAbridged);
	Sentence apartment_reading_list_choice_1 = Sentence(apartmentReadingListChoice1);
	Sentence apartment_reading_list_change_1 = Sentence(apartmentReadingListChange1);
	Sentence apartment_reading_list_choice_2 = Sentence(apartmentReadingListChoice2);
	Sentence apartment_reading_list_shower_1 = Sentence(apartmentReadingListShower1);
	Sentence apartment_reading_list_choice_3 = Sentence(apartmentReadingListChoice3);
	Sentence apartment_reading_list_leave_yes = Sentence(apartmentReadingListLeaveYes);
	Sentence apartment_reading_list_leave_No1 = Sentence(apartmentReadingListLeaveNo1);
	Sentence apartment_reading_list_leave_No2 = Sentence(apartmentReadingListLeaveNo2);
	Sentence apartment_reading_list_leave_No3 = Sentence(apartmentReadingListLeaveNo3);
	Sentence apartment_reading_list_leave_No4 = Sentence(apartmentReadingListLeaveNo4);
	Sentence apartment_reading_list_leave_No5 = Sentence(apartmentReadingListLeaveNo5);
	Sentence apartment_reading_list_leave_No6 = Sentence(apartmentReadingListLeaveNo6);
	Sentence apartment_reading_list_leave_No7 = Sentence(apartmentReadingListLeaveNo7);

	/* -------------- CROWDED STREET --------------*/

	Sentence street_crowded_intro = Sentence(streetCrowdedIntro);
	Sentence street_crowded_intro_abridged = Sentence(streetCrowdedIntroAbridged);
	Sentence street_crowded_choice_1 = Sentence(streetCrowdedChoice1);
	Sentence street_crowded_approach_1 = Sentence(streetCrowdedApproach1);
	Sentence street_crowded_approach_2 = Sentence(streetCrowdedApproach2);
	Sentence street_crowded_approach_3 = Sentence(streetCrowdedApproach3);
	Sentence street_crowded_approach_dirty = Sentence(streetCrowdedApproachDirty);
	Sentence street_crowded_approach_clean = Sentence(streetCrowdedApproachClean);
	Sentence street_crowded_choice_2 = Sentence(streetCrowdedChoice2);
	Sentence street_crowded_walk_1 = Sentence(streetCrowdedWalk1);

	/* -------------- SUPERMARKET --------------*/

	Sentence supermarket_intro = Sentence(supermarketIntro);
	Sentence supermarket_clean = Sentence(supermarketClean);
	Sentence supermarket_dirty = Sentence(supermarketDirty);
	Sentence supermarket_forget = Sentence(supermarketForget);
	Sentence supermarket_correct = Sentence(supermarketCorrect);
	Sentence supermarket_bad_1 = Sentence(supermarketBad1);
	Sentence supermarket_bad_2 = Sentence(supermarketBad2);
	Sentence supermarket_bad_3 = Sentence(supermarketBad3);
	Sentence supermarket_bad_4 = Sentence(supermarketBad4);
	Sentence supermarket_bad_5 = Sentence(supermarketBad5);
	Sentence supermarket_next = Sentence(supermarketNext);
	Sentence supermarket_previous = Sentence(supermarketPrevious);
	Sentence supermarket_thinking = Sentence(supermarketThinking);
	Sentence supermarket_wrong_guess_1 = Sentence(supermarketWrongGuess1);
	Sentence supermarket_wrong_guess_2 = Sentence(supermarketWrongGuess2);
	Sentence supermarket_right_guess = Sentence(supermarketRightGuess);

	/* -------------- STREET AGAIN --------------*/

	Sentence street_ignored_crowd = Sentence(streetIgnoredCrowd);
	Sentence street_approached_crowd = Sentence(streetApproachedCrowd);
	Sentence street_approached_crowd_abridged = Sentence(streetApproachedCrowdAbridged);
	Sentence street_choice_1 = Sentence(streetChoice1);
	Sentence street_walk_home_1 = Sentence(streetWalkHome1);
	Sentence street_choice_2 = Sentence(streetChoice2);
	Sentence street_examine_1 = Sentence(streetExamine1);
	Sentence street_examine_2 = Sentence(streetExamine2);
	Sentence street_examine_match = Sentence(streetExamineMatch);
	Sentence street_choice_3 = Sentence(streetChoice3);
	Sentence street_choice_walk_supermarket_1 = Sentence(streetWalkSupermarket1);

	/* -------------- BACK IN APARTMENT --------------*/


	Sentence ending_two_1 = Sentence(endingTwo1);
	Sentence ending_two_2 = Sentence(endingTwo2);
	Sentence ending_three_1 = Sentence(endingThree1);
	Sentence ending_three_2 = Sentence(endingThree2);
	Sentence credits_one = Sentence(creditsOne);
	Sentence credits_two = Sentence(creditsTwo);
	Sentence credits_three = Sentence(creditsThree);


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
