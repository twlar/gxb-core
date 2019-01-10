#pragma once

namespace graphene { namespace chain {

   class transaction_context {
      public:
        transaction_context(database &d, uint64_t origin, fc::microseconds max_trx_cpu_us);

        void pause_billing_timer();

        void resume_billing_timer();

        void checktime() const;

        uint64_t get_cpu_usage() const
        {
            return transaction_cpu_usage_us;
        }

      private:
        void dispatch_action(const action &a, uint64_t receiver);
        inline void dispatch_action(const action &a)
        {
            dispatch_action(a, a.contract_id);
        };

      private:
        friend class apply_context;

      public:
        database &db() const { assert(_db); return *_db; }
        uint64_t get_trx_origin() const { return trx_origin;  }

      private:
        database*                           _db;
        uint64_t                            trx_origin;
        uint64_t                            cross_contract_calling_count = 0;
        std::map<account_id_type, uint64_t> ram_usage_statistics;

        mutable fc::time_point              start;
        mutable fc::time_point              _deadline;
        mutable fc::time_point              pause_time;
        mutable int64_t                     pause_cpu_usage_us = 0;
        mutable int64_t                     transaction_cpu_usage_us = 0;
   };
} }
