//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2026
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace td {

struct TdMetrics {
  // === UpdatesManager gauges ===
  static std::atomic<int64_t> pending_pts_updates_count;
  static std::atomic<int64_t> postponed_pts_updates_count;
  static std::atomic<int64_t> running_get_difference;

  // === UpdatesManager counters ===
  static std::atomic<int64_t> get_difference_total;
  static std::atomic<int64_t> process_pending_calls;
  static std::atomic<int64_t> process_postponed_calls;

  // === Client output queue counters ===
  static std::atomic<int64_t> output_events_produced;
  static std::atomic<int64_t> output_events_consumed;

  // === SQLite aggregate counters ===
  static std::atomic<int64_t> sqlite_step_count;
  static std::atomic<int64_t> sqlite_step_total_us;
  static std::atomic<int64_t> sqlite_exec_count;
  static std::atomic<int64_t> sqlite_exec_total_us;
  static std::atomic<int64_t> sqlite_write_tx_count;

  // === MessageDb / DialogDb ===
  static std::atomic<int64_t> msg_db_flush_count;
  static std::atomic<int64_t> msg_db_pending_writes;
  static std::atomic<int64_t> dlg_db_flush_count;
  static std::atomic<int64_t> dlg_db_pending_writes;

  // === Binlog ===
  static std::atomic<int64_t> binlog_flush_count;

  // === Flood control ===
  static std::atomic<int64_t> flood_wait_count;
  static std::atomic<int64_t> flood_wait_total_seconds;
  static std::atomic<int64_t> flood_wait_max_seconds;
  static std::atomic<int64_t> slowmode_wait_count;
  static std::atomic<int64_t> slowmode_wait_total_seconds;
  static std::atomic<int64_t> flood_wait_timeout_exceeded;

  // === Message send lifecycle ===
  static std::atomic<int64_t> send_message_success;
  static std::atomic<int64_t> send_message_failed;

  // === Per-query SQLite stats ===
  struct QueryStat {
    int64_t count = 0;
    int64_t total_us = 0;
  };

  static std::mutex query_stats_mutex_;
  static std::unordered_map<std::string, QueryStat> query_stats_;

  static void record_query(const char *sql, int64_t elapsed_us) {
    if (sql == nullptr) {
      return;
    }
    std::lock_guard<std::mutex> lock(query_stats_mutex_);
    auto &s = query_stats_[sql];
    s.count++;
    s.total_us += elapsed_us;
  }

  struct QueryStatEntry {
    std::string sql;
    int64_t count;
    int64_t total_us;
  };

  static std::vector<QueryStatEntry> snapshot_query_stats() {
    std::lock_guard<std::mutex> lock(query_stats_mutex_);
    std::vector<QueryStatEntry> result;
    result.reserve(query_stats_.size());
    for (auto &[sql, stat] : query_stats_) {
      result.push_back({sql, stat.count, stat.total_us});
    }
    return result;
  }
};

}  // namespace td
