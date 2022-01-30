/* Código Atualizado para versão atual do FreeFire... */
/*
 * Decidi liberar este código devido estarem vendendo sem minha autorização
 * O Nome da função é Trigger Bot Magnet ( Tiro Automático ao encontrar inimigo Visível )
 * FREEEEEEEEEEEEEEEEEEEEEEEEEEEEE
 *
 * EM BREVE MAIS CÓDIGO, ACESSE NOSSO DISCORD: 
 * https://discord.gg/YXmRxRDUXp
 * YTB: https://www.youtube.com/c/GODSTEAMOFICIAL
 * Autor do código: Scott
**/


class TriggerBot{
public:
    enum FireMode
    {
        MANUL,
        AUTO
    };

    enum FireStatus
    {
        NONE,
        FIRING
    };
};

// Namespace : COW.GamePlay
// classe    : internal class Player : AttackableEntity
// Address   :  GetActiveWeapon() { } // RVA: 0xB49EE4
static void *Player_GetActiveWeapon(void *LocalPlayer)
{
    void *(*_Player_GetActiveWeapon)(void *LocalPlayer) = (void *(*)(void*)) getRealOffset(0xB49EE4);
    return _Player_GetActiveWeapon(LocalPlayer);
}

// Namespace : COW
// classe    : internal class GameFacade
// Address   : Player CurrentLocalPlayer() { } // RVA: 0x1515958
void *GameFacade_CurrentLocalPlayer()
{
    void *(*_CurrentLocalPlayer)() = (void*(*)())getRealOffset(0x1515958);
    return _CurrentLocalPlayer();
}

// Namespace : COW
// classe    : internal class GameFacade
// Address   : CurrentMatch() { } // RVA: 0x1515568
void *GameFacade_CurrentMatch()
{
    void *(*_CurrentMatch)() = (void*(*)())getRealOffset(0x1515568);
    return _CurrentMatch();
}

void (*orig_TriggerBot)(void *_this, int32_t pFireStatus, int32_t pFireMode);
void hook_TriggerBot(void *_this, int32_t pFireStatus, int32_t pFireMode)
{
    // [ _this ] Verificar se a função foi carregada!
    if(_this != NULL)
    {
        // [ Match ] Verificar se estou na partida
        void *Match = GameFacade_CurrentMatch();
        if (Match != NULL)
        {
            // [ LocalPlayer ] Verificar se meu local foi inicializado.
            void *LocalPlayer = GameFacade_CurrentLocalPlayer();
            if (LocalPlayer != NULL)
            {
                // [ Variável ] Use o botão para ativar a função
                if( Variável )
                {
                    // [ pGetActiveWeapon ] Estou com uma arma na mão.
                    void *pGetActiveWeapon = Player_GetActiveWeapon(LocalPlayer);
                    if ( pGetActiveWeapon )
                    {
                        // Adicione um (Visible Check) aqui dentro para não pegar inimigos dentro do cover.
                        // Exemplo
                        /*
                         * if(VisibleCheck(Player)){
                         *   pFireMode = TriggerBot::AUTO;
                         *   pFireMode = TriggerBot::AUTO;
                         * }
                         * o código ficará assim! com Visible Check
                         * */
                        
                        // [ pFireStatus ] Estou em disparando
                        pFireStatus = TriggerBot::FIRING;
                        // [ pFireMode ] Modo de tiro ( disparo Automático )
                        pFireMode = TriggerBot::AUTO;
                    }
                }
            }
        }
    }
    return orig_TriggerBot(_this, pFireStatus, pFireMode);
}

// Onde identificar o local da address. Caso o jogo atualize para uma nova versão :)
// Namespace : COW.GamePlay
// classe    : internal abstract class AKOPKPIDGEJ
// Address   : public void KBNOKPOCLED(AKOPKPIDGEJ.OOCNCAKCHNO NPMEDEOKBID, AKOPKPIDGEJ.HHMOMGDFCCJ OCANOIDGCHL = 0) { } // RVA: 0xDB1388

//Hookando a função
MSHookFunction((void *) getRealOffset(0xDB1388), (void *) &hook_TriggerBot, (void **) &orig_TriggerBot);
