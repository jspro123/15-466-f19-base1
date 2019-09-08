#include "StoryMode.hpp"

#include "Sprite.hpp"
#include "DrawSprites.hpp"
#include "Load.hpp"
#include "data_path.hpp"
#include "gl_errors.hpp"
#include "MenuMode.hpp"



Sprite const* supermarket_left = nullptr;
Sprite const* supermarket_front = nullptr;
Sprite const* supermarket_top = nullptr;
Sprite const* supermarket_color = nullptr;
Sprite const* supermarket_sign = nullptr;


Sprite const *sprite_left_select = nullptr;
Sprite const *sprite_right_select = nullptr;

Load< SpriteAtlas > sprites(LoadTagDefault, []() -> SpriteAtlas const * {
	SpriteAtlas const *ret = new SpriteAtlas(data_path("supermarket"));

	supermarket_left = &ret->lookup("supermarket-left");
	supermarket_front = &ret->lookup("supermarket-front");
	supermarket_top = &ret->lookup("supermarket-top");
	supermarket_color = &ret->lookup("supermarket-color");
	supermarket_sign = &ret->lookup("supermarket-sign");

	return ret;
});

StoryMode::StoryMode() {
}

StoryMode::~StoryMode() {
}

bool StoryMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {
	if (Mode::current.get()) {
		return false;
	}

	return false;
}

void StoryMode::update(float elapsed) {
	if (Mode::current.get() == this) {
		//there is no menu displayed! Make one:
		enter_scene();
	}
}

void StoryMode::enter_scene() {
	//just entered this scene, adjust flags and build menu as appropriate:
	std::vector< MenuMode::Item > items;
	glm::vec2 at(INDENT, view_max.y - 50.0f);


	//Returns the number of lines that sentence will need
	auto get_number_sentences = [](std::string const& sentence) {
		Sprite const* chr;
		float combined_width = 0.0;
		for (size_t pos = 0; pos < sentence.size(); pos++) {
			chr = &sprites->lookup(sentence.substr(pos, 1));
			combined_width += (chr->max_px.x - chr->min_px.x) * FONT_SIZE;
		}

		return ceil(combined_width / 1000.0f);
	};

	auto add_text = [&items,&at,&get_number_sentences](Sentence sentence) {
		items.emplace_back(sentence.text, nullptr, FONT_SIZE, 0, 
						  sentence.wait_to_print, nullptr, at);
		at.x = INDENT;
		at.y -= LINE_SKIP * get_number_sentences(sentence.text) * FONT_SIZE;
		at.y -= LINE_SKIP * FONT_SIZE;
	};

	//Makes the text instantly appear on the screen (no "typing" illusion)
	auto add_text_quick = [&items, &at, &get_number_sentences](Sentence sentence) {
		items.emplace_back(sentence.text, nullptr, FONT_SIZE, -1, -1.0f, nullptr, at);
		at.x = INDENT;
		at.y -= LINE_SKIP * get_number_sentences(sentence.text) * FONT_SIZE;
		at.y -= LINE_SKIP * FONT_SIZE;
	};

	auto add_choice = [&items,&at,&get_number_sentences](Sentence sentence, std::function< void(MenuMode::Item const &) > const &fn) {
		items.emplace_back(sentence.text, nullptr, FONT_SIZE, 0, sentence.wait_to_print, 
						  fn, at + glm::vec2(INDENT * FONT_SIZE, 0.0f));

		at.y -= LINE_SKIP * get_number_sentences(sentence.text) * FONT_SIZE;
		at.y -= 4.0f;
	};

	auto skip_lines= [&at]() {
		at.y -= LINE_SKIP * FONT_SIZE;
	};

	//The "automata". Controls everything about the game state.

	if (states == Opening) {
		add_text(opening_text_1);
		add_text(opening_text_2);

		skip_lines();

		add_choice(return_key, [this](MenuMode::Item const&) {
			states = Apartment;
			Mode::current = shared_from_this();
			});
	} else if (states == Apartment) {
		if (apartment_search.failed_search == true) {
			add_text(apartment_intro_search_failure);
		}
		else if (apartment_search.searched_bed == true) {
			add_text(apartment_intro_choice_search_bed_1);
		}
		else if (apartment_search.searched_desk == true) {
			add_text(apartment_intro_choice_search_desk_1);
		}

		if (apartment_search.first_choice == true) {
			add_text(apartment_intro);
		} else if(apartment_search.first_choice == false) {
			add_text(apartment_intro_abridged);
		}

		skip_lines();

		add_choice(apartment_intro_choice_1, [this](MenuMode::Item const&) {

			if (apartment_search.first_choice == true) {
				apartment_search.first_choice = false;
				apartment_search.searched_bed = true;
				apartment_search.failed_search = false;
			}
			else if (apartment_search.searched_bed == true) {
				apartment_search.failed_search = true;
			}
			else if (apartment_search.searched_bed == false) {
				states = LeavingApartment;
				apartment_search.found_in_bed = true;
			}
			Mode::current = shared_from_this();
			});

		skip_lines();

		add_choice(apartment_intro_choice_2, [this](MenuMode::Item const&) {

			if (apartment_search.first_choice == true) {
				apartment_search.first_choice = false;
				apartment_search.searched_desk = true;
				apartment_search.failed_search = false;
			}
			else if (apartment_search.searched_desk == true) {
				apartment_search.failed_search = true;
			}
			else if (apartment_search.searched_desk == false) {
				states = LeavingApartment;
				apartment_search.found_in_bed = false;
			}
			Mode::current = shared_from_this();
			});

	} else if (states == LeavingApartment) {
		if (apartment_leave.first_choice && apartment_search.found_in_bed == true) {
			add_text(apartment_intro_choice_search_bed_2);
			add_text(apartment_reading_list);
		}
		else if (apartment_leave.first_choice && apartment_search.found_in_bed == false) {
			add_text(apartment_intro_choice_search_desk_2);
			add_text(apartment_reading_list);
		}

		if (apartment_leave.tried_shower == true) {
			apartment_leave.tried_shower = false;
			add_text(apartment_reading_list_shower_1);
		}
		else if (apartment_leave.clean_clothes == true &&
			apartment_leave.remove_clothes_choice == false) {
			apartment_leave.remove_clothes_choice = true;
			add_text(apartment_reading_list_change_1);
		}
		else if (apartment_leave.tried_leave == true) {
			apartment_leave.tried_leave = false;
			switch (apartment_leave.leave_dirty) {
			case 1:
				add_text(apartment_reading_list_leave_No1);
				break;
			case 2:
				add_text(apartment_reading_list_leave_No2);
				break;
			case 3:
				add_text(apartment_reading_list_leave_No3);
				break;
			case 4:
				add_text(apartment_reading_list_leave_No4);
				break;
			case 5:
				add_text(apartment_reading_list_leave_No5);
				break;
			case 6:
				add_text(apartment_reading_list_leave_No6);
				break;
			}

			apartment_leave.leave_dirty++;
		}

		if (!apartment_leave.first_choice && !apartment_leave.clean_clothes) {
			add_text(apartment_reading_list_abridged);
		} else if (!apartment_leave.first_choice && apartment_leave.clean_clothes) {
			add_text(apartment_reading_list_u_abridged);
		}

		if (apartment_leave.remove_clothes_choice == false) {
			skip_lines();
			add_choice(apartment_reading_list_choice_1, [this](MenuMode::Item const&) {
				apartment_leave.first_choice = false;
				apartment_leave.clean_clothes = true;
				Mode::current = shared_from_this();
				});
		}

		skip_lines();

		add_choice(apartment_reading_list_choice_2, [this](MenuMode::Item const&) {
			apartment_leave.first_choice = false;
			apartment_leave.tried_shower = true;
			Mode::current = shared_from_this();
			});

		skip_lines();

		add_choice(apartment_reading_list_choice_3, [this](MenuMode::Item const&) {
			apartment_leave.first_choice = false;
			if (apartment_leave.clean_clothes == true || apartment_leave.leave_dirty == 7) {
				states = CrowdStreet;
			}
			apartment_leave.tried_leave = true;
			Mode::current = shared_from_this();
			});

	}
	else if (states == CrowdStreet) {
		if (crowded_street.first_choice && apartment_leave.clean_clothes) {
			add_text(apartment_reading_list_leave_yes);
			add_text(street_crowded_intro);
		}
		else if (crowded_street.first_choice && !apartment_leave.clean_clothes) {
			add_text(apartment_reading_list_leave_No7);
			add_text(street_crowded_intro);
		}

		if (crowded_street.approach_crowd == true) {
			crowded_street.approach_crowd = false;
			switch (crowded_street.approach_number) {
			case 1:
				add_text(street_crowded_approach_1);
				break;
			case 2:
				add_text(street_crowded_approach_2);
				break;
			}
			crowded_street.approach_number++;
		}

		if (!crowded_street.first_choice) {
			add_text(street_crowded_intro_abridged);
		}
		
		skip_lines();

		add_choice(street_crowded_choice_1, [this](MenuMode::Item const&) {
			crowded_street.first_choice = false;
			if (crowded_street.approach_number == 3) {
				states = WalkOrApproach;
			}
			crowded_street.approach_crowd = true;
			Mode::current = shared_from_this();
			});

		skip_lines();

		add_choice(street_crowded_choice_2, [this](MenuMode::Item const&) {
			crowded_street.first_choice = false;
			states = WalkOrApproach;
			crowded_street.continue_walking = true;
			Mode::current = shared_from_this();
			});
		
	} else if (states == WalkOrApproach) {
		if (crowded_street.continue_walking) {
			states = Supermarket;
			add_text(street_crowded_walk_1);
		} else if (crowded_street.approach_crowd && apartment_leave.clean_clothes) {
			add_text(street_crowded_approach_3);
			states = Supermarket;
			add_text(street_crowded_approach_clean);
		} else if (crowded_street.approach_crowd && !apartment_leave.clean_clothes) {
			add_text(street_crowded_approach_3);
			states = CreditsOne;
			add_text(street_crowded_approach_dirty);
		}

		skip_lines();

		add_choice(return_key, [this](MenuMode::Item const&) {
			Mode::current = shared_from_this();
			});

	} else if (states == Supermarket) {
		Sentence clerk_comments = apartment_leave.clean_clothes ? supermarket_clean : supermarket_dirty;

		if (!supermarket.flipped_pages) {
			if (supermarket.first_choice) {
				add_text(supermarket_intro);
				add_text(clerk_comments);
				if (crowded_street.approach_crowd) {
					add_text(supermarket_forget);
				}
				else {
					skip_lines();
					states = GoingBack;
					add_choice(return_key, [this](MenuMode::Item const&) {
						Mode::current = shared_from_this();
						});
				}
			} else if(supermarket.attempt_number == 2){
				add_text(supermarket_wrong_guess_1);
				add_text(supermarket_thinking);
			}
		} else {
			if (supermarket.first_choice) {
				add_text_quick(supermarket_intro);
				add_text_quick(clerk_comments);
				if (crowded_street.approach_crowd) {
					add_text_quick(supermarket_forget);
				}
			}
			else if (supermarket.attempt_number == 2) {
				add_text_quick(supermarket_wrong_guess_1);
				add_text_quick(supermarket_thinking);
			}
		}


		if (!supermarket.next_page && crowded_street.approach_crowd) {
			skip_lines();
			add_choice(supermarket_correct, [this](MenuMode::Item const&) {
				states = LeavingSupermarket;
				supermarket.got_matches = true;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_bad_1, [this](MenuMode::Item const&) {
				if (supermarket.attempt_number == 2) {
					states = LeavingSupermarket;
				}
				supermarket.first_choice = false;
				supermarket.attempt_number = 2;
				supermarket.flipped_pages = false;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_bad_2, [this](MenuMode::Item const&) {
				if (supermarket.attempt_number == 2) {
					states = LeavingSupermarket;
				}
				supermarket.first_choice = false;
				supermarket.attempt_number = 2;
				supermarket.flipped_pages = false;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_next, [this](MenuMode::Item const&) {
				supermarket.flipped_pages = true;
				supermarket.next_page = true;
				Mode::current = shared_from_this();
				});
		} else if(supermarket.next_page && crowded_street.approach_crowd){
			skip_lines();
			add_choice(supermarket_bad_3, [this](MenuMode::Item const&) {
				if (supermarket.attempt_number == 2) {
					states = LeavingSupermarket;
				}
				supermarket.first_choice = false;
				supermarket.attempt_number = 2;
				supermarket.flipped_pages = false;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_bad_4, [this](MenuMode::Item const&) {
				if (supermarket.attempt_number == 2) {
					states = LeavingSupermarket;
				}
				supermarket.first_choice = false;
				supermarket.attempt_number = 2;
				supermarket.flipped_pages = false;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_bad_5, [this](MenuMode::Item const&) {
				if (supermarket.attempt_number == 2) {
					states = LeavingSupermarket;
				}
				supermarket.first_choice = false;
				supermarket.attempt_number = 2;
				supermarket.flipped_pages = false;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(supermarket_previous, [this](MenuMode::Item const&) {
				supermarket.flipped_pages = true;
				supermarket.next_page = false;
				Mode::current = shared_from_this();
				});
		}

	} else if (states == LeavingSupermarket) {
		if (supermarket.got_matches) {
			add_text(supermarket_right_guess);
		}
		else {
			add_text(supermarket_wrong_guess_2);
		}
		states = GoingBack;
		add_choice(return_key, [this](MenuMode::Item const&) {
			Mode::current = shared_from_this();
			});

	} else if (states == GoingBack) {
		if (!crowded_street.approach_crowd) {
			states = EndingTwo;
			add_text(street_ignored_crowd);
			add_choice(return_key, [this](MenuMode::Item const&) {
				Mode::current = shared_from_this();
				});
		}
		
		if (empty_street.tried_supermarket) {
			empty_street.tried_supermarket = false;
			add_text(street_choice_walk_supermarket_1);
		} else if (empty_street.tried_examine) {
			empty_street.tried_examine = false;
			if (!empty_street.examined_post_no_matches) {
				add_text(street_examine_1);
				empty_street.examined_post_no_matches = true;
			} else {
				add_text(street_examine_2);
			}
		}

		if (empty_street.first_choice && crowded_street.approach_crowd) {
			add_text(street_approached_crowd);
		} else if (!empty_street.first_choice && crowded_street.approach_crowd){
			add_text(street_approached_crowd_abridged);
		}

		if (crowded_street.approach_crowd) {
			skip_lines();
			add_choice(street_choice_1, [this](MenuMode::Item const&) {
				empty_street.first_choice = false;
				states = LeavingStreet;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(street_choice_2, [this](MenuMode::Item const&) {
				empty_street.first_choice = false;
				if (supermarket.got_matches && empty_street.examined_post_no_matches) {
					states = LeavingStreet;
					empty_street.examined_post_matches = true;
				}
				empty_street.tried_examine = true;
				Mode::current = shared_from_this();
				});
			skip_lines();
			add_choice(street_choice_3, [this](MenuMode::Item const&) {
				empty_street.first_choice = false;
				empty_street.tried_supermarket = true;
				Mode::current = shared_from_this();
				});
		}

	} else if (states == LeavingStreet) {
		if (!empty_street.examined_post_matches) {
			states = EndingTwo;
			add_text(street_walk_home_1);
		} else {
			states = EndingThree;
			add_text(street_examine_match);
		}

		skip_lines();
		add_choice(return_key, [this](MenuMode::Item const&) {
			Mode::current = shared_from_this();
			});

	} else if (states == EndingTwo) {
		add_text(ending_two_1);
		add_text(ending_two_2);
		states = CreditsTwo;
		add_choice(return_key, [this](MenuMode::Item const&) {
			Mode::current = shared_from_this();
			});

	} else if (states == EndingThree) {
		add_text(ending_three_1);
		add_text(ending_three_2);
		states = CreditsThree;
		add_choice(return_key, [this](MenuMode::Item const&) {
			Mode::current = shared_from_this();
			});
	} else if (states == CreditsOne) {
		add_text(credits_one);
		add_choice(exit_key, [this](MenuMode::Item const&) {
			exit(0);
			Mode::current = shared_from_this();
			});
	} else if (states == CreditsTwo) {
		add_text(credits_two);
		add_choice(exit_key, [this](MenuMode::Item const&) {
		exit(0);
		Mode::current = shared_from_this();
		});
	} else if (states == CreditsThree) {
		add_text(credits_three);
		add_choice(exit_key, [this](MenuMode::Item const&) {
		exit(0);
		Mode::current = shared_from_this();
		});
	}

	std::shared_ptr< MenuMode > menu = std::make_shared< MenuMode >(items);
	menu->atlas = sprites;
	menu->left_select = sprite_left_select;
	menu->right_select = sprite_right_select;
	menu->view_min = view_min;
	menu->view_max = view_max;
	menu->background = shared_from_this();
	Mode::current = menu;
}

void StoryMode::draw(glm::uvec2 const &drawable_size) {
	//clear the color buffer:
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//use alpha blending:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//don't use the depth test:
	glDisable(GL_DEPTH_TEST);

	{ //use a DrawSprites to do the drawing:
		DrawSprites draw(*sprites, view_min, view_max, drawable_size, DrawSprites::AlignPixelPerfect);
		glm::vec2 ul = glm::vec2(view_min.x, view_max.y);
		draw.draw(*supermarket_color, ul);
		draw.draw(*supermarket_top, ul);
		draw.draw(*supermarket_left, ul);
		draw.draw(*supermarket_front, ul);
		draw.draw(*supermarket_sign, ul);
	}
	GL_ERRORS(); //did the DrawSprites do something wrong?
}
