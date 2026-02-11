# AI Coding Agent Guide for MyProject

## Project Overview
MyProject is an Unreal Engine 5.6 game project with a focus on modern rendering features (ray tracing, virtual shadow maps, dynamic global illumination). Single runtime module architecture with built-in EnhancedInput support for player input handling.

**Engine Version:** UE 5.6  
**Platform:** Windows (Win64)  
**Languages:** C++ (game code) + C# (build scripts)

---

## Module Architecture

### Primary Module: MyProject
- **Location:** `Source/MyProject/`
- **Files:**
  - `MyProject.h` - Module header (currently minimal, defines module entry point)
  - `MyProject.cpp` - Module implementation (uses `IMPLEMENT_PRIMARY_GAME_MODULE`)
  - `MyProject.Build.cs` - Unreal Build Tool (UBT) configuration

### Build Script Pattern (MyProject.Build.cs)
The module declares dependencies via `ModuleRules`:
- **Public Dependencies:** Core, CoreUObject, Engine, InputCore, EnhancedInput
- **Private Dependencies:** (Currently empty - add gameplay systems here)

*Note:* Leave `PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs` unchanged to maintain consistent compilation.

---

## Build System & Workflows

### Available Build Configurations
All tasks run from `C:\Program Files\Epic Games\UE_5.6` (Engine root) via batch scripts in `Engine\Build\BatchFiles\`:

- **Debug/DebugGame/Development/Test/Shipping** - Game builds (Win64)
- **MyProjectEditor** variants - Editor builds for development

#### Using Build Tasks
Invoke via VS Code Tasks (Ctrl+Shift+B):
```
MyProjectEditor Win64 Development Build  → Compile editor for iterative development
MyProject Win64 Development Build        → Package runtime game
MyProject Win64 Shipping Rebuild         → Full clean build for distribution
```

**Key Flags:**
- `-waitmutex` (all tasks) - Prevents concurrent build conflicts
- Rebuild tasks auto-depend on Clean task

### Manual Build Commands
If rebuilding via terminal from UE5.6 folder:
```powershell
Engine\Build\BatchFiles\Build.bat MyProjectEditor Win64 Development "C:\...\MyProject.uproject" -waitmutex
```

---

## Project-Specific Conventions

### Input System
- **Framework:** Enhanced Input System (EnhancedInput plugin, editor-enabled)
- **Pattern:** Use InputActionValue and IMC (Input Mapping Context) for action-based input
- **Where to Extend:** Inherit from APlayerController and call `SetupInputComponent()` to bind actions

### Rendering Configuration
Modern UE5 defaults enabled in `Config/DefaultEngine.ini`:
- Ray tracing enabled (`r.RayTracing=True`)
- Virtual shadow maps (`r.Shadow.Virtual.Enable=1`)
- Dynamic GI via Lumen (`r.DynamicGlobalIlluminationMethod=1`)
- Mesh distance fields for shadowing (`r.GenerateMeshDistanceFields=True`)

**Impact on Development:** Shaders compile with advanced features; significantly slower iteration in Debug builds. Disable ray tracing conditionally in editor if compile times are prohibitive.

### Game Mode & Default Map
- **Default Game Map:** `/Engine/Maps/Templates/OpenWorld` (OpenWorld template)
- **Configure Custom:** Edit `Config/DefaultEngine.ini` section `[/Script/EngineSettings.GameMapsSettings]`

---

## Target Rules & Platform Setup

### Build Targets (Source/*.Target.cs)
- **MyProjectTarget** (Game) - Runtime executable
- **MyProjectEditorTarget** (Editor) - Editor executable
- Both: Engine 5.6, Win64 only, include MyProject module

**Platform Extension:** To support other platforms (Mac, Linux), add to `ExtraModuleNames` and define platform-specific code guards (`#if PLATFORM_WINDOWS`).

---

## Critical Developer Patterns

### Adding New Game Classes
1. Create header/source files in `Source/MyProject/` subdirectories (e.g., `Characters/`, `Pawns/`, `GameModes/`)
2. Add to `MyProject.Build.cs` if new public dependencies needed
3. Use Unreal macros:
   - `UCLASS()` for actors/components (public reflection)
   - `UPROPERTY(EditAnywhere)` for designer exposure
   - `UFUNCTION()` for RPC/blueprint callability

### Module Loading
Modules load in `Default` phase (see `MyProject.uproject` - not deferred). For plugin dependencies, edit the uproject while editor is closed.

---

## Debugging & Iteration

### Hot Reload (Editor)
- Compile changes with "MyProjectEditor Win64 Development Build" task
- In-editor "Compile" button reloads C++ code without restarting engine
- **Caveat:** Complex memory changes may require full editor restart

### Console Variables
Access via Unreal Console (`~` key in-game/editor):
```
r.RayTracing 0          # Disable ray tracing for debugging
r.Lumen.Supported 0     # Disable Lumen GI
stat RHI                # Profile rendering performance
```

Edit `Config/DefaultEngine.ini` for persistent defaults.

---

## Key File Locations

- **Game Config:** `Config/DefaultEngine.ini`, `Config/DefaultGame.ini`, `Config/DefaultInput.ini`
- **Source Root:** `Source/MyProject/`
- **Build Scripts:** `Source/*.Target.cs`, `Source/MyProject/MyProject.Build.cs`
- **Engine Binaries:** `C:\Program Files\Epic Games\UE_5.6\Engine\`
- **Project Binaries:** `Binaries/Win64/` (populated after build)

---

## Common Tasks for AI Agents

| Task | How |
|------|-----|
| Add a new character class | Create `Source/MyProject/Characters/MyCharacter.h/.cpp`, inherit from `ACharacter` |
| Expose variable to designer | Use `UPROPERTY(EditAnywhere)` on class member |
| Handle player input | Override `SetupInputComponent()` in APlayerController subclass, bind EnhancedInput actions |
| Configure game startup | Edit `[/Script/EngineSettings.GameMapsSettings]` in DefaultEngine.ini |
| Debug rendering | Toggle console vars (`r.RayTracing`, `r.Lumen.Supported`) or edit DefaultEngine.ini |

