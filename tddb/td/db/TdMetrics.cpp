//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2026
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "td/db/TdMetrics.h"

namespace td {

std::atomic<int64_t> TdMetrics::pending_pts_updates_count{0};
std::atomic<int64_t> TdMetrics::postponed_pts_updates_count{0};
std::atomic<int64_t> TdMetrics::running_get_difference{0};
std::atomic<int64_t> TdMetrics::get_difference_total{0};
std::atomic<int64_t> TdMetrics::process_pending_calls{0};
std::atomic<int64_t> TdMetrics::process_postponed_calls{0};
std::atomic<int64_t> TdMetrics::output_events_produced{0};
std::atomic<int64_t> TdMetrics::output_events_consumed{0};
std::atomic<int64_t> TdMetrics::sqlite_step_count{0};
std::atomic<int64_t> TdMetrics::sqlite_step_total_us{0};
std::atomic<int64_t> TdMetrics::sqlite_exec_count{0};
std::atomic<int64_t> TdMetrics::sqlite_exec_total_us{0};
std::atomic<int64_t> TdMetrics::sqlite_write_tx_count{0};
std::atomic<int64_t> TdMetrics::msg_db_flush_count{0};
std::atomic<int64_t> TdMetrics::msg_db_pending_writes{0};
std::atomic<int64_t> TdMetrics::dlg_db_flush_count{0};
std::atomic<int64_t> TdMetrics::dlg_db_pending_writes{0};
std::atomic<int64_t> TdMetrics::binlog_flush_count{0};

std::atomic<int64_t> TdMetrics::flood_wait_count{0};
std::atomic<int64_t> TdMetrics::flood_wait_total_seconds{0};
std::atomic<int64_t> TdMetrics::flood_wait_max_seconds{0};
std::atomic<int64_t> TdMetrics::slowmode_wait_count{0};
std::atomic<int64_t> TdMetrics::slowmode_wait_total_seconds{0};
std::atomic<int64_t> TdMetrics::flood_wait_timeout_exceeded{0};

std::atomic<int64_t> TdMetrics::send_message_success{0};
std::atomic<int64_t> TdMetrics::send_message_failed{0};

std::mutex TdMetrics::query_stats_mutex_;
std::unordered_map<std::string, TdMetrics::QueryStat> TdMetrics::query_stats_;

}  // namespace td
