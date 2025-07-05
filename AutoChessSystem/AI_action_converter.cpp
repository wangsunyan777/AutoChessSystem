#include "AI_action_converter.h"

const int BOARD_ROWS = 6;
const int BOARD_COLS = 10;
const int STATE_DIM = 60;  // �򻯺��״̬ά�ȣ�8+30+18+4

// �򻯵Ķ����ռ䣺24ά��12�ƶ�+12������
const std::vector<std::pair<int, int>> ACTION_OFFSETS = {
    // ����1��8������ (actions 0-7)
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
    // ����2��4����Ҫ���� (actions 8-11) 
    {-2, 0}, {2, 0}, {0, -2}, {0, 2}
};

std::vector<float> gameState(Soldier** AllSoldiers, int SoldierCount, int selfCount, int turnCount) {
    std::vector<float> state_vector(STATE_DIM, 0.0f);

    if (selfCount < 0 || selfCount >= SoldierCount || !AllSoldiers[selfCount]->isAlive) {
        std::cout << "���棺��ǰʿ����Ч��������" << std::endl;
        return state_vector;
    }

    Soldier* current_soldier = AllSoldiers[selfCount];
    std::cout << "����״̬: ʿ��" << selfCount << " λ��(" << current_soldier->x << "," << current_soldier->y << ")" << std::endl;

    int idx = 0;

    // ===== ������Ϣ (8ά) =====
    // λ�ù�һ����[-1,1]
    state_vector[idx++] = (current_soldier->x - 5.5f) / 4.5f;  // x�����һ��
    state_vector[idx++] = (current_soldier->y - 3.5f) / 2.5f;  // y�����һ��
    state_vector[idx++] = (float)current_soldier->HP / current_soldier->MAXHP;  // Ѫ���ٷֱ�

    // ����one-hot����
    if (current_soldier->type == 1) {      // warrior
        state_vector[idx] = 1.0f;
    }
    else if (current_soldier->type == 2) { // mage
        state_vector[idx + 1] = 1.0f;
    }
    else if (current_soldier->type == 3) { // killer
        state_vector[idx + 2] = 1.0f;
    }
    idx += 3;

    state_vector[idx++] = current_soldier->MANUVER / 2.0f;      // �ƶ�����һ��
    state_vector[idx++] = current_soldier->RANGE / 3.0f;        // ������Χ��һ��

    // ===== ������Ϣ (30ά) =====
    std::vector<std::pair<float, Soldier*>> enemies;
    for (int i = 0; i < SoldierCount; ++i) {
        if (i != selfCount && AllSoldiers[i]->isAlive &&
            AllSoldiers[i]->side != current_soldier->side) {
            float distance = sqrt(pow(AllSoldiers[i]->x - current_soldier->x, 2) +
                pow(AllSoldiers[i]->y - current_soldier->y, 2));
            enemies.push_back({ distance, AllSoldiers[i] });
        }
    }

    // ����������ȡ�����5��
    std::sort(enemies.begin(), enemies.end());
    int max_enemies = std::min(5, (int)enemies.size());

    for (int i = 0; i < 5; ++i) {
        if (i < max_enemies) {
            Soldier* enemy = enemies[i].second;
            // ���λ�ù�һ��
            float rel_x = (enemy->x - current_soldier->x) / 9.0f;
            float rel_y = (enemy->y - current_soldier->y) / 5.0f;

            state_vector[idx++] = std::max(-1.0f, std::min(1.0f, rel_x));
            state_vector[idx++] = std::max(-1.0f, std::min(1.0f, rel_y));
            state_vector[idx++] = (float)enemy->HP / enemy->MAXHP;

            // ���ֱ���
            if (enemy->type == 1) {
                state_vector[idx] = 1.0f;
            }
            else if (enemy->type == 2) {
                state_vector[idx + 1] = 1.0f;
            }
            else if (enemy->type == 3) {
                state_vector[idx + 2] = 1.0f;
            }
            idx += 3;
        }
        else {
            idx += 6; // �����յĵ��˲�λ
        }
    }

    // ===== ������Ϣ (18ά) =====
    std::vector<std::pair<float, Soldier*>> allies;
    for (int i = 0; i < SoldierCount; ++i) {
        if (i != selfCount && AllSoldiers[i]->isAlive &&
            AllSoldiers[i]->side == current_soldier->side) {
            float distance = sqrt(pow(AllSoldiers[i]->x - current_soldier->x, 2) +
                pow(AllSoldiers[i]->y - current_soldier->y, 2));
            allies.push_back({ distance, AllSoldiers[i] });
        }
    }

    // ����������ȡ�����3��
    std::sort(allies.begin(), allies.end());
    int max_allies = std::min(3, (int)allies.size());

    for (int i = 0; i < 3; ++i) {
        if (i < max_allies) {
            Soldier* ally = allies[i].second;
            // ���λ�ù�һ��
            float rel_x = (ally->x - current_soldier->x) / 9.0f;
            float rel_y = (ally->y - current_soldier->y) / 5.0f;

            state_vector[idx++] = std::max(-1.0f, std::min(1.0f, rel_x));
            state_vector[idx++] = std::max(-1.0f, std::min(1.0f, rel_y));
            state_vector[idx++] = (float)ally->HP / ally->MAXHP;

            // ���ֱ���
            if (ally->type == 1) {
                state_vector[idx] = 1.0f;
            }
            else if (ally->type == 2) {
                state_vector[idx + 1] = 1.0f;
            }
            else if (ally->type == 3) {
                state_vector[idx + 2] = 1.0f;
            }
            idx += 3;
        }
        else {
            idx += 6; // �����յĶ��Ѳ�λ
        }
    }

    // ===== ȫ����Ϣ (4ά) =====
    int friendly_count = 0, enemy_count = 0;
    float friendly_hp = 0.0f, enemy_hp = 0.0f;

    for (int i = 0; i < SoldierCount; ++i) {
        if (!AllSoldiers[i]->isAlive) continue;

        float hp_ratio = (float)AllSoldiers[i]->HP / AllSoldiers[i]->MAXHP;
        if (AllSoldiers[i]->side == current_soldier->side) {
            friendly_count++;
            friendly_hp += hp_ratio;
        }
        else {
            enemy_count++;
            enemy_hp += hp_ratio;
        }
    }

    state_vector[idx++] = friendly_count / 6.0f;              // ����������һ��
    state_vector[idx++] = enemy_count / 6.0f;                 // �з�������һ��
    state_vector[idx++] = std::min(turnCount / 50.0f, 1.0f);  // �غ�����һ��

    // ��Ѫ������
    float total_hp = friendly_hp + enemy_hp;
    state_vector[idx++] = (total_hp > 0) ? (friendly_hp / total_hp) : 0.5f;

    std::cout << "״̬�������: ����" << friendly_count << "��, �з�" << enemy_count << "��" << std::endl;
    return state_vector;
}

std::vector<int> getValidActions(Soldier** AllSoldiers, int SoldierCount, int selfCount) {
    std::vector<int> valid_actions;

    if (selfCount < 0 || selfCount >= SoldierCount || !AllSoldiers[selfCount]->isAlive) {
        std::cout << "ʿ����Ч���޷��ж�" << std::endl;
        return valid_actions;
    }

    Soldier* current_soldier = AllSoldiers[selfCount];
    int current_x = current_soldier->x;
    int current_y = current_soldier->y;

    std::cout << "������Ч����: ʿ����(" << current_x << "," << current_y << ")" << std::endl;

    // ����ƶ����� (0-11)
    for (int i = 0; i < 12; ++i) {
        int dr = ACTION_OFFSETS[i].first;
        int dc = ACTION_OFFSETS[i].second;
        int new_row = current_y + dr;
        int new_col = current_x + dc;

        // ���߽�
        if (new_row < 1 || new_row > BOARD_ROWS || new_col < 1 || new_col > BOARD_COLS) {
            continue;
        }

        // ����ƶ�����
        int distance = abs(dr) + abs(dc);
        if (distance > current_soldier->MANUVER) {
            continue;
        }

        // ���λ���Ƿ�ռ��
        bool occupied = false;
        for (int j = 0; j < SoldierCount; ++j) {
            if (j != selfCount && AllSoldiers[j]->isAlive &&
                AllSoldiers[j]->x == new_col && AllSoldiers[j]->y == new_row) {
                occupied = true;
                break;
            }
        }

        if (!occupied) {
            valid_actions.push_back(i);
        }
    }

    // ��鹥������ (12-23)
    for (int i = 0; i < 12; ++i) {
        int dr = ACTION_OFFSETS[i].first;
        int dc = ACTION_OFFSETS[i].second;
        int target_row = current_y + dr;
        int target_col = current_x + dc;

        // ���߽�
        if (target_row < 1 || target_row > BOARD_ROWS || target_col < 1 || target_col > BOARD_COLS) {
            continue;
        }

        // ��鹥������
        float distance = sqrt(dr * dr + dc * dc);
        if (distance > current_soldier->RANGE) {
            continue;
        }

        // ���Ŀ��λ���Ƿ��е���
        bool has_enemy = false;
        for (int j = 0; j < SoldierCount; ++j) {
            if (AllSoldiers[j]->isAlive &&
                AllSoldiers[j]->x == target_col && AllSoldiers[j]->y == target_row &&
                AllSoldiers[j]->side != current_soldier->side) {
                has_enemy = true;
                break;
            }
        }

        if (has_enemy) {
            valid_actions.push_back(12 + i);  // ��������ID
        }
    }

    std::cout << "�ҵ� " << valid_actions.size() << " ����Ч����" << std::endl;
    return valid_actions;
}