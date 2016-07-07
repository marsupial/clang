//------------------------------------------------------------------------------
// CLING - the C++ LLVM-based InterpreterG :)
//
// This file is dual-licensed: you can choose to license it under the University
// of Illinois Open Source License or the GNU Lesser General Public License. See
// LICENSE.TXT for details.
//------------------------------------------------------------------------------

#ifndef LLVM_CLANG_BASIC_CLING_H
#define LLVM_CLANG_BASIC_CLING_H

#include "llvm/Support/cling.h"

namespace cling {

/// \brief Forward declaration need for friendship.
class DeclUnloader;
class ParserStateRAII;

/// \brief Enabling this hack makes the template substitution more permissive
/// and allows for replacement with non-canonical types.  This is usefull in
/// the case of client code emulating opaque typedefs and/or wanting to recover
/// the template instance name as the user would have written if (s)he
/// expanded the default paramater explicitly.   For example the user might
/// have type: \c vector<int32_t> and the client wants to see:
/// \c std::vector<int32_t,std::allocator<int32_t> >
   
class HackForDefaultTemplateArg {
  /// \brief Private RAII object that set and reset the hack state.

  static bool AllowNonCanonicalSubstEnabled;
  bool OldValue;
public:

  HackForDefaultTemplateArg();
  ~HackForDefaultTemplateArg();
  
  static bool AllowNonCanonicalSubst();
};

#ifdef CLING_OBJC_SUPPORT
  namespace objectivec {
    /// \brief Interface for CodeGen of Objective-C runtime objects.
    /// When compiling objective c code, clang emits stubs for addresses that will
    /// be filled in at runtime by the linker.  We need to the stubs to point to
    /// the addresses as they are known now.

    class IObjCLookup {
    public:
      // Not neccessary, but compilers be complaining
      virtual ~IObjCLookup() {}

      /// \brief Lookup the given selector in the Objective-C runtime.
      ///
      /// \param[in] name - The selector's name.
      ///
      /// \returns the address of the selector in the runtime
      ///
      virtual void* getSelector(const char* name) = 0;

      /// \brief Lookup the given class in the Objective-C runtime.
      ///
      /// \param[in] name - The Class name.
      ///
      /// \returns the address of the Class in the runtime
      ///
      virtual void* getClass(const char* name) = 0;
    };

    /// \brief The global Objective-C lookup helper for CodeGen.
    /// This should only be set once during initialization.
    ///
    extern IObjCLookup* gInstance;

  } // namespace objectivec
#endif // CLING_OBJC_SUPPORT

} // namespace cling

#endif
