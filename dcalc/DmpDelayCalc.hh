



namespace sta {

class ArcDelayCalc;
class StaState;

ArcDelayCalc *
makeDmpCeffElmoreDelayCalc(StaState *sta);
ArcDelayCalc *
makeDmpCeffTwoPoleDelayCalc(StaState *sta);

} // namespace
