# CrustEngine sources
## Description
// TODO
## Notes
### To read
- What does `explicit` mean in C++?
- What does `[[nodiscard]]` mean in C++?
- std::move
- What's best getter for pointer - can I return reference to pointer?

### TODO
- Fix *.obj files loader
- getter fixes - reference vs pointer vs value
- Perspective projector math model 
- Maybe render loop should be in core and in this loop we could call each window 'tick' method to update it's content - that way we could handle many windows in one loop.

### Decision making
- We use `const char*` instead of `std::string` for performance and memory allocation control reasons.