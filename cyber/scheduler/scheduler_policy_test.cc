/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <gtest/gtest.h>

#include "cyber/cyber.h"
#include "cyber/scheduler/policy/choreography.h"
#include "cyber/scheduler/policy/classic.h"
#include "cyber/scheduler/processor.h"

namespace apollo {
namespace cyber {
namespace scheduler {

void func() {}
TEST(SchedulerPolicyTest, choreo) {
  auto processor = std::make_shared<Processor>();
  std::shared_ptr<ProcessorContext> ctx;
  ctx.reset(new ChoreographyContext());
  processor->BindContext(ctx);
  ctx->BindProc(processor);

  std::shared_ptr<CRoutine> cr = std::make_shared<CRoutine>(func);
  auto task_id = GlobalData::RegisterTaskName("choreo");
  cr->set_id(task_id);
  EXPECT_TRUE(static_cast<ChoreographyContext *>(ctx.get())->Enqueue(cr));
  processor->Start();
  ctx->ShutDown();
}

TEST(SchedulerPolicyTest, classic) {
  auto processor = std::make_shared<Processor>();
  std::shared_ptr<ProcessorContext> ctx;
  ctx.reset(new ClassicContext());
  processor->BindContext(ctx);
  ctx->BindProc(processor);

  std::shared_ptr<CRoutine> cr = std::make_shared<CRoutine>(func);
  auto task_id = GlobalData::RegisterTaskName("classic");
  cr->set_id(task_id);
  processor->Start();
  ctx->ShutDown();
}

}  // namespace scheduler
}  // namespace cyber
}  // namespace apollo
