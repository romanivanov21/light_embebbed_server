/**
 *   Файл: function_wrapper.h
 *
 *   Описание: wrapper над std::function
 */

#ifndef _FUNCTION_WRAPPER_H_
#define _FUNCTION_WRAPPER_H_

#include <memory>

class function_wrapper
{
public:
    function_wrapper() = default;

    ~function_wrapper() = default;

    /**
     *   @param f вызываемя функция
     */
    template <typename F>
    function_wrapper( F&& f ) : impl_ ( new impl_type<F> ( std::move( f ) ) ) { }

    /**
     *  @brief перегрузка оператора(), для определения функционального объекта
     */
    void operator()();

    /**
     *  @brief определение конструктора перемещения, для использования move semantics
     */
    function_wrapper( function_wrapper&& other );

    /**
     *  @brief определение оператора присваивания с перемещением, для использования move semantics
     */
    function_wrapper& operator=( function_wrapper&& other );

    function_wrapper( const function_wrapper& copy ) = delete;

    function_wrapper( function_wrapper& copy ) = delete;

    function_wrapper& operator=(const function_wrapper& copy ) = delete;

private:
    struct impl_base
    {
        virtual void call() = 0;

        virtual ~impl_base() = default;
    };

    template <class F>
    struct impl_type : impl_base
    {
        F f_;
        impl_type( F&& f ) : f_( std::move( f ) ) { }
        void call() override { f_(); }
    };

    std::unique_ptr<impl_base> impl_;
};

#endif //_FUNCTION_WRAPPER_H_