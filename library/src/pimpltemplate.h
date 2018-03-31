#if !defined(INCLUDED_PIMPLTEMPLATE_H)
#define INCLUDED_PIMPLTEMPLATE_H  1

/*
 * =====================================================================================
 *
 *       Filename:  pimpltemplate.h
 *
 *    Description:  来源loki开源库的实现 
 *                  该类的实现是为了隐藏类成员的实现
 *
 *        Version:  1.0
 *        Created:  09/16/2017 04:49:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), wwei@landicorp.com
 *        Company:  Landicorp
 *   Organization:  GNU
 *
 * =====================================================================================
 */

///  \defgroup PimplGroup Pimpl 

#ifndef LOKI_INHERITED_PIMPL_NAME
#define LOKI_INHERITED_PIMPL_NAME d
#endif

#ifndef LOKI_INHERITED_RIMPL_NAME
#define LOKI_INHERITED_RIMPL_NAME d
#endif

namespace WangV
{

    //////////////////////////////////////////
    ///  \class ConstPropPtr
    ///
    ///  \ingroup PimplGroup
    ///   Simple const propagating smart pointer
    ///   Is the default smart pointer of Pimpl.
    //////////////////////////////////////////

    template<class T>
    struct ConstPropPtr
    {
        explicit ConstPropPtr(T* p) : ptr_(p) {}
        ~ConstPropPtr() { delete  ptr_; ptr_ = 0; }
        T* operator->()    { return  ptr_; }
        T& operator*()    { return *ptr_; }
        const T* operator->() const    { return  ptr_; }
        const T& operator*()  const    { return *ptr_; }
    
    private:
        ConstPropPtr();
        ConstPropPtr(const ConstPropPtr&);
        ConstPropPtr& operator=(const ConstPropPtr&);
        T* ptr_;
    };


    ////////////////////////////////////////////////////////////////////////////////
    ///  \class Pimpl
    ///
    ///  \ingroup PimplGroup
    ///
    ///  Implements the Pimpl idiom. It's a wrapper for a smart pointer which
    ///  automatically creates and deletes the implementation object and adds
    ///  const propagation to the smart pointer.
    ///  
    ///  \par Usage
    ///  see test/Pimpl
    ////////////////////////////////////////////////////////////////////////////////

    template
    <    
        class T, 
        typename Pointer = ConstPropPtr<T>
    >
    class Pimpl 
    {
    public:

        typedef T Impl;

        Pimpl() : ptr_(new T)
        {}

        ~Pimpl()
        {
            // Don't compile with incomplete type
            //
            // If compilation breaks here make sure
            // the compiler does not auto-generate the 
            // destructor of the class hosting the pimpl:
            // - implement the destructor of the class 
            // - don't inline the destructor
            typedef char T_must_be_defined[sizeof(T) ? 1 : -1 ];
        }


        T* operator->()
        {
            return ptr_.operator->();
        }

        T& operator*()
        {
            return ptr_.operator*();
        }

        const T* operator->() const
        {
            return ptr_.operator->();
        }

        const T& operator*() const
        {
            return ptr_.operator*();
        }

        Pointer& wrapped()
        {
            return ptr_;
        }

        const Pointer& wrapped() const
        {
            return ptr_;
        }


    private:
        Pimpl(const Pimpl&);
        Pimpl& operator=(const Pimpl&);

        Pointer ptr_;
    };


    template<class T, typename Pointer = ConstPropPtr<T> >
    struct PimplOwner 
    {    
        Pimpl<T,Pointer> LOKI_INHERITED_PIMPL_NAME;
    };


    //////////////////////////////////////////
    /// \class  ImplOf
    ///
    /// \ingroup PimplGroup
    /// Convenience template for the 
    /// implementations which Pimpl points to.
    //////////////////////////////////////////

    template<class T>
    struct ImplOf;


    //////////////////////////////////////////
    /// \class  PImplOf
    ///
    /// \ingroup PimplGroup
    /// Convenience template which uses ImplOf
    /// as implementation structure
    //////////////////////////////////////////


    template<class T, template<class> class Ptr = ConstPropPtr>
    struct PimplOf
    {
        typedef T Impl;

        // declare pimpl
        typedef Pimpl<ImplOf<T>, Ptr<ImplOf<T> > > Type;

        // inherit pimpl
        typedef PimplOwner<ImplOf<T>, Ptr<ImplOf<T> > > Owner;
    };


    template<class T, class UsedPimpl = typename PimplOf<T>::Type >
    struct RimplOf
    {
        typedef typename UsedPimpl::Impl & Type;

        class Owner
        {
            UsedPimpl pimpl;

        public:
            Owner() : LOKI_INHERITED_RIMPL_NAME(*pimpl)
            {}

            Type LOKI_INHERITED_RIMPL_NAME;
        };

    };
  
}

#endif /* !defined(INCLUDED_PIMPLTEMPLATE_H) */
