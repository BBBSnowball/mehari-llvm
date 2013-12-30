#include "llvm/IR/Function.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {

  struct PrepareAlwaysInline : public FunctionPass {
    static char ID; 
    PrepareAlwaysInline() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &func) {
      // TODO add attribute just for a custom set of functions?
      func.addFnAttr(Attribute::AlwaysInline);
      return true;
    }
  };
}

char PrepareAlwaysInline::ID = 0;
static RegisterPass<PrepareAlwaysInline>
Y("prepare-always-inline", "Add function attribute 'AlwaysInline' to prepare inline operations");
