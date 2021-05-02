#pragma once
#include <memory>
namespace seraphim  {
	using std::shared_ptr;
	using std::unique_ptr;
	class BoxMatcher : public std::enable_shared_from_this<BoxMatcher>
	{
	private:
		shared_ptr<BoxMatcher> left_{nullptr};
		shared_ptr<BoxMatcher> right_{nullptr};
		bool  bOR_{false};
	public:
		shared_ptr<BoxMatcher>  orOperator(shared_ptr<BoxMatcher> mathcher) {
			return std::make_shared<BoxMatcher>(shared_from_this(), mathcher,true);
		};
		shared_ptr<BoxMatcher> andOperator(shared_ptr<BoxMatcher>  mathcher) {
			return std::make_shared<BoxMatcher>(shared_from_this(), mathcher, false);
		}
		BoxMatcher() = default;

		BoxMatcher(shared_ptr<BoxMatcher> first, shared_ptr<BoxMatcher> second, bool bOR) :left_(first), right_(second), bOR_(bOR) {};


		virtual bool  match() { 
			if (bOR_) {
				return left_->match() || right_->match();
			}
			return  left_->match() && right_->match();		
		};
		virtual  ~BoxMatcher() {

		}

		
	};
};
