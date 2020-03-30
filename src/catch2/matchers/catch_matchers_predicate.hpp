/*
 *  Created by Martin Hořeňovský on 03/04/2017.
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_MATCHERS_GENERIC_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_MATCHERS_GENERIC_HPP_INCLUDED

#include <catch2/internal/catch_common.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/catch_meta.hpp>

#include <string>
#include <utility>

namespace Catch {
namespace Matchers {

namespace Detail {
    std::string finalizeDescription(const std::string& desc);
} // namespace Detail

template <typename T, typename Predicate>
class PredicateMatcher final : public MatcherBase<T> {
    Predicate m_predicate;
    std::string m_description;
public:

    PredicateMatcher(Predicate&& elem, std::string const& descr)
        :m_predicate(std::forward<Predicate>(elem)),
        m_description(Detail::finalizeDescription(descr))
    {}

    bool match( T const& item ) const override {
        return m_predicate(item);
    }

    std::string describe() const override {
        return m_description;
    }
};

    /**
     * Creates a matcher that calls delegates `match` to the provided predicate.
     *
     * The user has to explicitly specify the argument type to the matcher
     */
    template<typename T, typename Pred>
    PredicateMatcher<T, Pred> Predicate(Pred&& predicate, std::string const& description = "") {
        static_assert(is_callable<Pred(T)>::value, "Predicate not callable with argument T");
        static_assert(std::is_same<bool, FunctionReturnType<Pred, T>>::value, "Predicate does not return bool");
        return PredicateMatcher<T, Pred>(std::forward<Pred>(predicate), description);
    }

} // namespace Matchers
} // namespace Catch

#endif // TWOBLUECUBES_CATCH_MATCHERS_GENERIC_HPP_INCLUDED
