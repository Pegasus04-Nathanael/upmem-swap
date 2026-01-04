# UPMEM Swap Project - Plan de Développement

## Objectif du Projet
Développer une implémentation de **swap mémoire optimisé avec UPMEM DPU** pour [à spécifier].

## Phase 1 : Analyse & Design (2-4 semaines) ✅ EN COURS
- [ ] Définir l'algorithme principal
- [ ] Schématiser l'architecture (CPU-DPU interaction)
- [ ] Calculer la complexité (temps, mémoire WRAM/MRAM)
- [ ] Écrire les specs techniques

## Phase 2 : Implémentation Code (4-6 semaines) ⏳ PRÊT À COMMENCER
- [ ] Code HOST (host/main.c)
  - [ ] Allocation des DPUs
  - [ ] Chargement du programme
  - [ ] Orchestration des tâches
  - [ ] Communication DPU ↔ HOST

- [ ] Code DPU (dpu/main.c)
  - [ ] Kernels de traitement
  - [ ] Gestion mémoire (WRAM/MRAM)
  - [ ] Synchronisation (tasklets)

- [ ] Makefile de compilation

## Phase 3 : Tests & Benchmark (2-3 semaines) ⏸️ BLOCKÉ SDK
- [ ] Compilation avec UPMEM SDK
- [ ] Tests unitaires
- [ ] Benchmarks CPU vs DPU
- [ ] Optimisations

## Phase 4 : Validation (1 semaine) ⏸️ BLOCKÉ SDK
- [ ] Tests sur hardware réel (si dispo)
- [ ] Documentation finale
- [ ] Rapport de résultats

---

## Blocages Actuels
- ❌ **SDK UPMEM inaccessible** (serveurs down)
  - Workaround: Continuer phases 1-2
  - Contacter: https://www.upmem.com (Qualcomm depuis 2025)
  - GitHub: https://github.com/upmem/dpu_demo/issues

---

## Ressources Disponibles
- ✅ Exemples: `/opt/dpu_demo` (clonés dans container)
- ✅ Documentation: https://sdk.upmem.com/stable/
- ✅ GitHub UPMEM: https://github.com/upmem/

## À faire en premier
1. **Définir précisément** ce qu'on optimise avec UPMEM
2. **Écrire l'architecture** en markdown
3. **Commencer le code HOST** (shell du projet)
4. **Préparer le Makefile**
