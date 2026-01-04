# UPMEM SDK Setup Guide

## Current Situation

The official UPMEM SDK download servers are currently **inaccessible** (since Nov 23, 2025):
- `sdk.upmem.com` - Returns 403/404 errors
- `sdk-releases.upmem.com` - Access Denied (S3 Bucket)

This affects versions: 2023.1.0, 2024.2.0, 2025.1.0, and others.

## ✅ SOLUTION FOUND: Community Archive

A community member ([kagandikmen](https://github.com/kagandikmen)) has archived the UPMEM SDK:
- **Repository**: https://github.com/kagandikmen/upmem-sdk
- **Status**: Public, maintained, all versions available
- **License**: Community preservation (see repo disclaimer)

The Dockerfile has been updated to download from this archive automatically.

## Current Solution

The Dockerfile now:
1. ✅ Clones the UPMEM SDK archive from GitHub
2. ✅ Installs Git LFS (for large files)
3. ✅ Extracts SDK 2025.1.0 (Linux x86_64, Ubuntu 20.04)
4. ✅ Sets up environment variables
5. ✅ Clones UPMEM demo examples

## To Rebuild Container

```bash
# Clear old image
docker image prune

# Rebuild with new Dockerfile
codespace restart
# or
devcontainer rebuild
```

## Build Status

The devcontainer should now include:
- ✅ Full UPMEM SDK 2025.1.0
- ✅ Development tools (gcc, g++, make, python3)
- ✅ UPMEM demo examples
- ✅ DPU compilation toolchain

## Alternative: Manual SDK Download

If you prefer to download manually:

```bash
# Install Git LFS first
sudo apt install git-lfs

# Clone and extract
git clone https://github.com/kagandikmen/upmem-sdk.git
cd upmem-sdk
git lfs pull
cd 2025.1.0/ubuntu_20.04
tar xzf upmem-2025.1.0-Linux-x86_64.tar.gz
```

## References
- Archive Repo: https://github.com/kagandikmen/upmem-sdk
- Original Issue: https://github.com/upmem/dpu_demo/issues/17
- UPMEM Documentation: https://sdk.upmem.com/stable/
- UPMEM GitHub: https://github.com/upmem

## Important Notes

⚠️ **Legal/License**:
- The archive repository uses files previously made publicly available by UPMEM
- For commercial use, contact Qualcomm/UPMEM directly
- See the archive repo disclaimer for full details

