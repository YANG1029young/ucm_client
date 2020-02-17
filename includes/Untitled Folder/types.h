/*
 * All rights reserved.
 * Any use of this source code is subject to a license agreement with the
 * Shanghai Hinge Electronic Technology Co.,Ltd.
 *
 * Date: 2018-11-19
 * Author: ryan
 */

#ifndef ARA_COM_E2EXF_TYPES_H
#define ARA_COM_E2EXF_TYPES_H

#include <ara/com/e2e/state_machine.h>

namespace ara
{
namespace com
{
namespace e2exf
{

class E2EResult
{
public:
    using E2EState = com::E2E_state_machine::E2EState;
    using E2ECheckStatus = com::E2E_state_machine::E2ECheckStatus;

    E2EResult() noexcept;

    E2EResult(E2EState state, E2ECheckStatus checkStatus) noexcept;

    E2EResult(const E2EResult&) = default;
    E2EResult(E2EResult&&) noexcept = default;

    E2EResult& operator=(const E2EResult&) = default;

    E2EResult& operator=(E2EResult&&) noexcept = default;

    ~E2EResult() noexcept = default;

    bool IsOK() const noexcept;

    E2EState GetE2EState() const noexcept;

    E2ECheckStatus GetE2ECheckStatus() const noexcept;

private:
    E2EState smState;
    E2ECheckStatus checkStatus;
};

}  // namespace e2exf
}  // namespace com
}  // namespace ara

#endif  // ARA_COM_E2EXF_TYPES_H
