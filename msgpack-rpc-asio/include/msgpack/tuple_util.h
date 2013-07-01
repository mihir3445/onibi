#pragma once
namespace std {

    // print std::tuple
    // 0
    inline std::ostream &operator<<(std::ostream &os, const std::tuple<> &t)
    {
        os << "()";
        return os;
    }

    // 1
    template<typename A1>
        inline std::ostream &operator<<(std::ostream &os, const std::tuple<A1> &t)
        {
            os 
                << "("
                << std::get<0>(t)
                << ")";
            return os;
        }

    // 2
    template<typename A1, typename A2>
        inline std::ostream &operator<<(std::ostream &os, const std::tuple<A1, A2> &t)
        {
            os 
                << "("
                << std::get<0>(t)
                << ", " << std::get<1>(t)
                << ")";
            return os;
        }

    // 3
    template<typename A1, typename A2, typename A3>
        inline std::ostream &operator<<(std::ostream &os, const std::tuple<A1, A2, A3> &t)
        {
            os 
                << "("
                << std::get<0>(t)
                << ", " << std::get<1>(t)
                << ", " << std::get<2>(t)
                << ")";
            return os;
        }

    // 4
    template<typename A1, typename A2, typename A3, typename A4>
        inline std::ostream &operator<<(std::ostream &os, const std::tuple<A1, A2, A3, A4> &t)
        {
            os 
                << "("
                << std::get<0>(t)
                << ", " << std::get<1>(t)
                << ", " << std::get<2>(t)
                << ", " << std::get<3>(t)
                << ")";
            return os;
        }


    // call_with_tuple
    // 0
    template<typename F>
        auto call_with_tuple(const F &handler, const std::tuple<> &args)->decltype(handler())
        {
            return handler();
        }

    // 1
    template<typename F, typename A1>
        auto call_with_tuple(const F &handler, const std::tuple<A1> &args)->decltype(handler(A1()))
        {
            return handler(std::get<0>(args));
        }

    // 2
    template<typename F, typename A1, typename A2>
        auto call_with_tuple(const F &handler, const std::tuple<A1, A2> &args)->decltype(handler(A1(), A2()))
        {
            return handler(std::get<0>(args), std::get<1>(args));
        }

    // 3
    template<typename F, typename A1, typename A2, typename A3>
        auto call_with_tuple(const F &handler, const std::tuple<A1, A2, A3> &args)->decltype(handler(A1(), A2(), A3()))
        {
            return handler(std::get<0>(args), std::get<1>(args), std::get<2>(args));
        }

    // 4
    template<typename F, typename A1, typename A2, typename A3, typename A4>
        auto call_with_tuple(const F &handler, const std::tuple<A1, A2, A3, A4> &args)->decltype(handler(A1(), A2(), A3(), A4()))
        {
            return handler(std::get<0>(args), std::get<1>(args), std::get<2>(args), std::get<3>(args));
        }

    // 7
    template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
        auto call_with_tuple(const F &handler, const std::tuple<A1, A2, A3, A4, A5, A6, A7> &args)->decltype(handler(A1(), A2(), A3(), A4(), A5(), A6(), A7()))
        {
            return handler(std::get<0>(args), std::get<1>(args), std::get<2>(args), std::get<3>(args), std::get<4>(args), std::get<5>(args), std::get<6>(args));
        }

    // 8
    template<typename F, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
        auto call_with_tuple(const F &handler, const std::tuple<A1, A2, A3, A4, A5, A6, A7, A8> &args)->decltype(handler(A1(), A2(), A3(), A4(), A5(), A6(), A7(), A8()))
        {
            return handler(std::get<0>(args), std::get<1>(args), std::get<2>(args), std::get<3>(args), std::get<4>(args), std::get<5>(args), std::get<6>(args), std::get<7>(args));
        }

    // call_with_tuple_void
    // 0
    template<typename F>
        void call_with_tuple_void(const F &handler, const std::tuple<> &args)
        {
            handler();
        }
    // 1
    template<typename F, typename A1>
        void call_with_tuple_void(const F &handler, const std::tuple<A1> &args)
        {
            handler(std::get<0>(args));
        }
    // 2
    template<typename F, typename A1, typename A2>
        void call_with_tuple_void(const F &handler, const std::tuple<A1, A2> &args)
        {
            handler(std::get<0>(args), std::get<1>(args));
        }
    // 3
    template<typename F, typename A1, typename A2, typename A3>
        void call_with_tuple_void(const F &handler, const std::tuple<A1, A2, A3> &args)
        {
            handler(std::get<0>(args), std::get<1>(args), std::get<2>(args));
        }
    // 4
    template<typename F, typename A1, typename A2, typename A3, typename A4>
        void call_with_tuple_void(const F &handler, const std::tuple<A1, A2, A3, A4> &args)
        {
            handler(std::get<0>(args), std::get<1>(args), std::get<2>(args), std::get<3>(args));
        }
}


namespace msgpack {

    // std::tuple pack
    // 0
    template <typename Stream>
        inline packer<Stream>& operator<< (packer<Stream>& o, const std::tuple<>& t)
        {
            o.pack_array(0);
            return o;
        }
    // 1
    template <typename Stream, typename A1>
        inline packer<Stream>& operator<< (packer<Stream>& o, const std::tuple<A1>& t)
        {
            o.pack_array(1);
            o.pack(std::get<0>(t));
            return o;
        }
    // 2
    template <typename Stream, typename A1, typename A2>
        inline packer<Stream>& operator<< (packer<Stream>& o, const std::tuple<A1, A2>& t)
        {
            o.pack_array(2);
            o.pack(std::get<0>(t));
            o.pack(std::get<1>(t));
            return o;
        }
    // 3
    template <typename Stream, typename A1, typename A2, typename A3>
        inline packer<Stream>& operator<< (packer<Stream>& o, const std::tuple<A1, A2, A3>& t)
        {
            o.pack_array(3);
            o.pack(std::get<0>(t));
            o.pack(std::get<1>(t));
            o.pack(std::get<2>(t));
            return o;
        }
    // 4
    template <typename Stream, typename A1, typename A2, typename A3, typename A4>
        inline packer<Stream>& operator<< (packer<Stream>& o, const std::tuple<A1, A2, A3, A4>& t)
        {
            o.pack_array(4);
            o.pack(std::get<0>(t));
            o.pack(std::get<1>(t));
            o.pack(std::get<2>(t));
            o.pack(std::get<3>(t));
            return o;
        }

    // std::tuple unpack
    // 0
    inline std::tuple<>& operator>> (object o, std::tuple<>& t)
    {
        if(o.type != type::ARRAY) { throw type_error(); }
        return t;
    }

    // 1
    template <typename A1>
        inline std::tuple<A1>& operator>> (object o, std::tuple<A1>& t)
        {
            if(o.type != type::ARRAY) { throw type_error(); }
            if(o.via.array.size > 0) {
                object* p = o.via.array.ptr;
                p->convert(&std::get<0>(t));
            }
            return t;
        }

    // 2
    template <typename A1, typename A2>
        inline std::tuple<A1, A2>& operator>> (object o, std::tuple<A1, A2>& t)
        {
            if(o.type != type::ARRAY) { throw type_error(); }
            if(o.via.array.size > 0) {
                object* p = o.via.array.ptr;
                p->convert(&std::get<0>(t));
                ++p;
                p->convert(&std::get<1>(t));
            }
            return t;
        }

    // 3
    template <typename A1, typename A2, typename A3>
        inline std::tuple<A1, A2, A3>& operator>> (object o, std::tuple<A1, A2, A3>& t)
        {
            if(o.type != type::ARRAY) { throw type_error(); }
            if(o.via.array.size > 0) {
                object* p = o.via.array.ptr;
                p->convert(&std::get<0>(t));
                ++p;
                p->convert(&std::get<1>(t));
                ++p;
                p->convert(&std::get<2>(t));
            }
            return t;
        }

    // 4
    template <typename A1, typename A2, typename A3, typename A4>
        inline std::tuple<A1, A2, A3, A4>& operator>> (object o, std::tuple<A1, A2, A3, A4>& t)
        {
            if(o.type != type::ARRAY) { throw type_error(); }
            if(o.via.array.size > 0) {
                object* p = o.via.array.ptr;
                p->convert(&std::get<0>(t));
                ++p;
                p->convert(&std::get<1>(t));
                ++p;
                p->convert(&std::get<2>(t));
                ++p;
                p->convert(&std::get<3>(t));
            }
            return t;
        }
}

