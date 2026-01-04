# upmem-swap

UPMEM swap memory optimization project.

## ✅ SDK Status

**RESOLVED!** The UPMEM SDK is now available from the community archive:
- Repository: https://github.com/kagandikmen/upmem-sdk
- Version: 2025.1.0 (Linux x86_64, Ubuntu 20.04)
- Status: ✅ Integrated in devcontainer

The dev container will automatically download and install the SDK.

## Getting Started

### Build the Dev Container
```bash
devcontainer rebuild
```

### Build the Project
```bash
make              # Build HOST application
make run          # Build and run
make check-sdk    # Verify SDK installation
make help         # Show all targets
```

### Project Structure
```
src/
├── host/        # HOST application (CPU side)
├── dpu/         # DPU kernels (coprocessor side)
docs/
├── PROJECT_PLAN.md
```

## Documentation
- [Project Plan](docs/PROJECT_PLAN.md)
- [SDK Setup](./devcontainer/SDK_SETUP.md)
- [UPMEM Official Docs](https://sdk.upmem.com/stable/)
- [DPU Demo Examples](https://github.com/upmem/dpu_demo)

## Troubleshooting

### SDK Installation Issues
If the devcontainer build fails:
1. Ensure Git LFS is available: `git lfs install`
2. Check: https://github.com/kagandikmen/upmem-sdk

### Build Issues
```bash
make clean        # Clean build artifacts
make check-sdk    # Verify SDK is installed
```

## Related Issues
- Original SDK access issue: https://github.com/upmem/dpu_demo/issues/17
- Community archive: https://github.com/kagandikmen/upmem-sdk