//
//  Move.h
//  basic
//
//  Created by leico on 2015/07/29.
//
//

#ifndef __basic__Move__
#define __basic__Move__

#include "ofMain.h"


template<typename T>
class Change{
	private:
		T       current;
		T       target;
		float   resist;
	public:
	
		/* ============================================ *
		 * Constructor/Destructor                       *
		 * ============================================ */
		 Change(void){};
		~Change(void){};

		 Change(const T& current, const T& target, const float resist) :
			 current(current)
		 , target(target)
		 , resist(resist)
		 {}
		
		/* ============================================ *
		 * Copy Constructor                             *
		 * ============================================ */
		 Change(const Change<T>& mother){
			 current = mother.current;
			 target  = mother.target;
			 resist  = mother.resist;
		 }

		/* ============================================ *
		 * Setup                                        *
		 * ============================================ */
		void Setup(const T& current, const T& target, const float resist){
			Current(current);
			Target (target);
			Resist (resist);
		}

		/* ============================================ *
		 * Get/Set Current                              *
		 * ============================================ */
		const T& Current(void){ return current; }
		const T& Current(const T& current){
			this -> current = current;
			return this -> current;
		}

		/* ============================================ *
		 * Get/Set Target                               *
		 * ============================================ */
		const T& Target(void){ return target; }
		const T& Target(const T& target){
			this -> target = target;
			return this -> target;
		}

		/* ============================================ *
		 * Get/Set Resist                               *
		 * ============================================ */
		const float Resist(void){ return resist; }
		const float Resist(const float resist){
			this -> resist = resist;
			return this -> resist;
		}

		/* ============================================ *
		 * Update                                       *
		 * ============================================ */
		const T& Update(void){
			current = current + (target - current) * resist;
			return Current();
		}

		/* ============================================ *
		 * Change<T> = Change<T>                        *
		 * ============================================ */
		Change<T>& operator=(const Change<T>& other){
			current = other.current;
			target  = other.target;
			resist  = other.resist;

			return (*this);
		}
};

#endif /* defined(__basic__Move__) */
