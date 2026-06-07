#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/plugin/Register.hh>
#include <gz/sim/components/Name.hh>
#include <gz/sim/components/Pose.hh>
#include <gz/sim/components/ExternalWorldWrenchCmd.hh>
#include <gz/math/Vector3.hh>
#include <gz/sim/Link.hh>

namespace gripper_plugins
{

class SpringPlugin:
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate
{
public:

    void Configure(
        const gz::sim::Entity &entity,
        const std::shared_ptr<const sdf::Element> &,
        gz::sim::EntityComponentManager &ecm,
        gz::sim::EventManager &) override
    {
        std::cout << "Plugin loaded!" << std::endl;

        std::cout << "Robot entity = "
                << entity
                << std::endl;
    }

    void PreUpdate(
        const gz::sim::UpdateInfo &,
        gz::sim::EntityComponentManager &ecm) override
    {
        counter++;

        if (!printedLinks)
        {
            printedLinks = true;

            ecm.Each<gz::sim::components::Name>(
            [&](const gz::sim::Entity &entity,
                const gz::sim::components::Name *name)
            {
                if (name->Data() == "R14")
                {
                    R14Entity = entity;

                    std::cout
                        << "FOUND R14: "
                        << R14Entity
                        << std::endl;
                }

                if (name->Data() == "R23")
                {
                    R23Entity = entity;

                    std::cout
                        << "FOUND R23: "
                        << R23Entity
                        << std::endl;
                }

                if (name->Data() == "R12")
                {
                    R12Entity = entity;

                    std::cout
                        << "FOUND R12: "
                        << R12Entity
                        << std::endl;
                }

                if (name->Data() == "R22")
                {
                    R22Entity = entity;

                    std::cout
                        << "FOUND R22: "
                        << R22Entity
                        << std::endl;
                }

                if (name->Data() == "R311")
                {
                    R311Entity = entity;

                    std::cout
                        << "FOUND R311: "
                        << R311Entity
                        << std::endl;
                }

                if (name->Data() == "R312")
                {
                    R312Entity = entity;

                    std::cout
                        << "FOUND R312: "
                        << R312Entity
                        << std::endl;
                }

                if (name->Data() == "L14")
                {
                    L14Entity = entity;

                    std::cout
                        << "FOUND L14: "
                        << L14Entity
                        << std::endl;
                }

                if (name->Data() == "L23")
                {
                    L23Entity = entity;

                    std::cout
                        << "FOUND L23: "
                        << L23Entity
                        << std::endl;
                }

                if (name->Data() == "L12")
                {
                    L12Entity = entity;

                    std::cout
                        << "FOUND L12: "
                        << L12Entity
                        << std::endl;
                }

                if (name->Data() == "L22")
                {
                    L22Entity = entity;

                    std::cout
                        << "FOUND L22: "
                        << L22Entity
                        << std::endl;
                }

                if (name->Data() == "L311")
                {
                    L311Entity = entity;

                    std::cout
                        << "FOUND L311: "
                        << L311Entity
                        << std::endl;
                }

                if (name->Data() == "L312")
                {
                    L312Entity = entity;

                    std::cout
                        << "FOUND L312: "
                        << L312Entity
                        << std::endl;
                }
                if (name->Data() == "R21")
                {
                    R21Entity = entity;

                    std::cout
                        << "FOUND R21: "
                        << R21Entity
                        << std::endl;
                }

                if (name->Data() == "L21")
                {
                    L21Entity = entity;

                    std::cout
                        << "FOUND L21: "
                        << L21Entity
                        << std::endl;
                }
                if (name->Data() == "gripper")
                {
                    modelEntity = entity;

                    std::cout
                        << "FOUND MODEL: "
                        << modelEntity
                        << std::endl;
                }

                return true;
            });

            std::cout << "==================================" << std::endl;
        }

        double k = 10000.0;

        if (R14Entity != gz::sim::kNullEntity &&
            R23Entity != gz::sim::kNullEntity &&
            R12Entity != gz::sim::kNullEntity &&
            R22Entity != gz::sim::kNullEntity &&
            R311Entity != gz::sim::kNullEntity &&
            R312Entity != gz::sim::kNullEntity &&
            L14Entity != gz::sim::kNullEntity &&
            L23Entity != gz::sim::kNullEntity &&
            L12Entity != gz::sim::kNullEntity &&
            L22Entity != gz::sim::kNullEntity &&
            L311Entity != gz::sim::kNullEntity &&
            L312Entity != gz::sim::kNullEntity &&
            R21Entity != gz::sim::kNullEntity &&
            L21Entity != gz::sim::kNullEntity &&
            modelEntity != gz::sim::kNullEntity
            )
        {
            auto poseR14 =
                ecm.Component<gz::sim::components::Pose>(
                    R14Entity);

            auto poseR23 =
                ecm.Component<gz::sim::components::Pose>(
                    R23Entity);

            auto poseR12 =
                ecm.Component<gz::sim::components::Pose>(
                    R12Entity);

            auto poseR22 =
                ecm.Component<gz::sim::components::Pose>(
                    R22Entity);

            auto poseR311 =
                ecm.Component<gz::sim::components::Pose>(
                    R311Entity);

            auto poseR312 =
                ecm.Component<gz::sim::components::Pose>(
                    R312Entity);

            auto poseL14 =
                ecm.Component<gz::sim::components::Pose>(
                    L14Entity);

            auto poseL23 =
                ecm.Component<gz::sim::components::Pose>(
                    L23Entity);

            auto poseL12 =
                ecm.Component<gz::sim::components::Pose>(
                    L12Entity);

            auto poseL22 =
                ecm.Component<gz::sim::components::Pose>(
                    L22Entity);

            auto poseL311 =
                ecm.Component<gz::sim::components::Pose>(
                    L311Entity);

            auto poseL312 =
                ecm.Component<gz::sim::components::Pose>(
                    L312Entity);

            auto poseR21 =
                ecm.Component<gz::sim::components::Pose>(
                    R21Entity);

            auto poseL21 =
                ecm.Component<gz::sim::components::Pose>(
                    L21Entity);

            auto poseModel =
                ecm.Component<gz::sim::components::Pose>(
                    modelEntity);

            if (poseR14 &&
                poseR23 &&
                poseR12 &&
                poseR22 &&
                poseR311 &&
                poseR312 &&
                poseL14 &&
                poseL23 &&
                poseL12 &&
                poseL22 &&
                poseL311 &&
                poseL312 &&
                poseR21 &&
                poseL21 &&
                poseModel)
            {
                auto R14 = poseR14->Data();
                auto R23 = poseR23->Data();
                auto R12 = poseR12->Data();
                auto R22 = poseR22->Data();
                auto R311 = poseR311->Data();
                auto R312 = poseR312->Data();
                auto R21 = poseR21->Data();

                auto L14 = poseL14->Data();
                auto L23 = poseL23->Data();
                auto L12 = poseL12->Data();
                auto L22 = poseL22->Data();
                auto L311 = poseL311->Data();
                auto L312 = poseL312->Data();
                auto L21 = poseL21->Data();

                auto modelPose = poseModel->Data();

                gz::math::Vector3d local0(0.0, 0.0, 0.0);
                gz::math::Vector3d localA(0.01828, 0.0, 0.00638);//in lik 12 for 22
                gz::math::Vector3d localB(0.0, 0.0, 0.01889);//in link 14 for 23
                gz::math::Vector3d localC(0.0, 0.0, 0.02091);//in link 311 for 21
                gz::math::Vector3d localD(0.0, -0.029, 0.02575);//in link 21 for 311
                gz::math::Vector3d localE(0.0, 0.0, 0.02115);//in link 312 for 23
                gz::math::Vector3d localF(0.0, -0.029, 0.0);//in link 23 for 312


                // Right side

                auto RA =
                    R12.Pos() +
                    R12.Rot().RotateVector(localA);

                auto RB =
                    R14.Pos() +
                    R14.Rot().RotateVector(localB);

                auto RC =
                    R311.Pos() +
                    R311.Rot().RotateVector(localC);

                auto RD =
                    R21.Pos() +
                    R21.Rot().RotateVector(localD);

                auto RE =
                    R312.Pos() +
                    R312.Rot().RotateVector(localE);

                auto RF =
                    R23.Pos() +
                    R23.Rot().RotateVector(localF);


                // Left side

                auto LA =
                    L12.Pos() +
                    L12.Rot().RotateVector(localA);

                auto LB =
                    L14.Pos() +
                    L14.Rot().RotateVector(localB);

                auto LC =
                    L311.Pos() +
                    L311.Rot().RotateVector(localC);

                auto LD =
                    L21.Pos() +
                    L21.Rot().RotateVector(localD);

                auto LE =
                    L312.Pos() +
                    L312.Rot().RotateVector(localE);

                auto LF =
                    L23.Pos() +
                    L23.Rot().RotateVector(localF);

                //changing the coordinates from base_link frame to world frame calculating errors and forces

                auto RAf =
                    modelPose.Rot().RotateVector(RA);

                auto RBf =
                    modelPose.Rot().RotateVector(RB);

                auto RCf =
                    modelPose.Rot().RotateVector(RC);

                auto RDf =
                    modelPose.Rot().RotateVector(RD);

                auto REf =
                    modelPose.Rot().RotateVector(RE);

                auto RFf =
                    modelPose.Rot().RotateVector(RF);

                auto LAf =
                    modelPose.Rot().RotateVector(LA);

                auto LBf =
                    modelPose.Rot().RotateVector(LB);

                auto LCf =
                    modelPose.Rot().RotateVector(LC);

                auto LDf =
                    modelPose.Rot().RotateVector(LD);

                auto LEf =
                    modelPose.Rot().RotateVector(LE);

                auto LFf =
                    modelPose.Rot().RotateVector(LF);

                auto R22f =
                    modelPose.Rot().RotateVector(
                        R22.Pos());

                auto R23f =
                    modelPose.Rot().RotateVector(
                        R23.Pos());

                auto L22f =
                    modelPose.Rot().RotateVector(
                        L22.Pos());

                auto L23f =
                    modelPose.Rot().RotateVector(
                        L23.Pos());




                auto errorRA = RAf - R22f;
                auto errorRB = RBf - R23f;
                auto errorRC = RCf - RDf;
                auto errorRE = REf - RFf;

                auto errorLA = LAf - L22f;
                auto errorLB = LBf - L23f;
                auto errorLC = LCf - LDf;
                auto errorLE = LEf - LFf;

                auto forceRA = -k * errorRA;
                auto forceRB = -k * errorRB;
                auto forceRC = -k * errorRC;
                auto forceRE = -k * errorRE;

                auto forceLA = -k * errorLA;
                auto forceLB = -k * errorLB;
                auto forceLC = -k * errorLC;
                auto forceLE = -k * errorLE;

                // Links

                gz::sim::Link R12Link(R12Entity);
                gz::sim::Link R22Link(R22Entity);

                gz::sim::Link R14Link(R14Entity);
                gz::sim::Link R23Link(R23Entity);

                gz::sim::Link R311Link(R311Entity);
                gz::sim::Link R21Link(R21Entity);

                gz::sim::Link R312Link(R312Entity);

                gz::sim::Link L12Link(L12Entity);
                gz::sim::Link L22Link(L22Entity);

                gz::sim::Link L14Link(L14Entity);
                gz::sim::Link L23Link(L23Entity);

                gz::sim::Link L311Link(L311Entity);
                gz::sim::Link L21Link(L21Entity);

                gz::sim::Link L312Link(L312Entity);

                // Right side

                R12Link.AddWorldForce(
                    ecm,
                    forceRA,
                    localA);

                R22Link.AddWorldForce(
                    ecm,
                    -forceRA,
                    local0);

                R14Link.AddWorldForce(
                    ecm,
                    forceRB,
                    localB);

                R23Link.AddWorldForce(
                    ecm,
                    -forceRB,
                    local0);

                R311Link.AddWorldForce(
                    ecm,
                    forceRC,
                    localC);

                R21Link.AddWorldForce(
                    ecm,
                    -forceRC,
                    localD);

                R312Link.AddWorldForce(
                    ecm,
                    forceRE,
                    localE);

                R23Link.AddWorldForce(
                    ecm,
                    -forceRE,
                    local0);

                // Left side

                L12Link.AddWorldForce(
                    ecm,
                    forceLA,
                    localA);

                L22Link.AddWorldForce(
                    ecm,
                    -forceLA,
                    local0);

                L14Link.AddWorldForce(
                    ecm,
                    forceLB,
                    localB);

                L23Link.AddWorldForce(
                    ecm,
                    -forceLB,
                    local0);

                L311Link.AddWorldForce(
                    ecm,
                    forceLC,
                    localC);

                L21Link.AddWorldForce(
                    ecm,
                    -forceLC,
                    localD);

                L312Link.AddWorldForce(
                    ecm,
                    forceLE,
                    localE);

                L23Link.AddWorldForce(
                    ecm,
                    -forceLE,
                    local0);
                
                double kAngle = 20.0;
                double targetAngle = 2.00171812;

                // World Z axes of the links
                auto z14 =
                    modelPose.Rot().RotateVector(
                        R14.Rot().RotateVector(
                            gz::math::Vector3d(0,0,1)));

                auto z23 =
                    modelPose.Rot().RotateVector(
                        R23.Rot().RotateVector(
                            gz::math::Vector3d(0,0,1)));

                auto zL14 =
                    modelPose.Rot().RotateVector(
                        L14.Rot().RotateVector(
                            gz::math::Vector3d(0,0,1)));

                auto zL23 =
                    modelPose.Rot().RotateVector(
                        L23.Rot().RotateVector(
                            gz::math::Vector3d(0,0,1)));

                // Current angles
                double angleR =
                    acos(
                        std::clamp(
                            z14.Dot(z23),
                            -1.0,
                            1.0));

                double angleL =
                    acos(
                        std::clamp(
                            zL14.Dot(zL23),
                            -1.0,
                            1.0));

                // Errors
                double errorAngleR =
                    angleR - targetAngle;

                double errorAngleL =
                    angleL - targetAngle;

                // Torque axis
                auto axisR = z14.Cross(z23);
                auto axisL = zL14.Cross(zL23);

                if (axisR.Length() > 1e-6)
                    axisR.Normalize();

                if (axisL.Length() > 1e-6)
                    axisL.Normalize();

                // Spring torques
                auto torqueR =
                    -kAngle *
                    errorAngleR *
                    axisR;

                auto torqueL =
                    -kAngle *
                    errorAngleL *
                    axisL;

                R23Link.AddWorldWrench(
                    ecm,
                    local0,
                    torqueR);

                // R14Link.AddWorldWrench(
                //     ecm,
                //     localB,
                //     -torqueR);

                L23Link.AddWorldWrench(
                    ecm,
                    local0,
                    torqueL);

                // L14Link.AddWorldWrench(
                //     ecm,
                //     localB,
                //     -torqueL);
                                
                // if (counter % 500 == 0)
                // {
                //     std::cout << "\n========================\n";

                //     std::cout << "RA  = " << RA << '\n';
                //     std::cout << "R22 = " << R22.Pos() << '\n';
                //     std::cout << "errorRA = " << errorRA << '\n';
                //     std::cout << "forceRA = " << forceRA << "\n\n";

                //     std::cout << "RB  = " << RB << '\n';
                //     std::cout << "R23 = " << R23.Pos() << '\n';
                //     std::cout << "errorRB = " << errorRB << '\n';
                //     std::cout << "forceRB = " << forceRB << "\n\n";

                //     std::cout << "RC  = " << RC << '\n';
                //     std::cout << "RD  = " << RD << '\n';
                //     std::cout << "errorRC = " << errorRC << '\n';
                //     std::cout << "forceRC = " << forceRC << "\n\n";

                //     std::cout << "RE  = " << RE << '\n';
                //     std::cout << "R23 = " << R23.Pos() << '\n';
                //     std::cout << "errorRE = " << errorRE << '\n';
                //     std::cout << "forceRE = " << forceRE << "\n\n";

                //     std::cout << "LA  = " << LA << '\n';
                //     std::cout << "L22 = " << L22.Pos() << '\n';
                //     std::cout << "errorLA = " << errorLA << '\n';
                //     std::cout << "forceLA = " << forceLA << "\n\n";

                //     std::cout << "LB  = " << LB << '\n';
                //     std::cout << "L23 = " << L23.Pos() << '\n';
                //     std::cout << "errorLB = " << errorLB << '\n';
                //     std::cout << "forceLB = " << forceLB << "\n\n";

                //     std::cout << "LC  = " << LC << '\n';
                //     std::cout << "LD  = " << LD << '\n';
                //     std::cout << "errorLC = " << errorLC << '\n';
                //     std::cout << "forceLC = " << forceLC << "\n\n";

                //     std::cout << "LE  = " << LE << '\n';
                //     std::cout << "L23 = " << L23.Pos() << '\n';
                //     std::cout << "errorLE = " << errorLE << '\n';
                //     std::cout << "forceLE = " << forceLE << '\n';

                //     std::cout << "========================\n";
                // }
        
            }
        }
    }
private:
    int counter = 0;
    bool printedLinks = false;
    gz::sim::Entity R14Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R23Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R12Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R22Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R311Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R312Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L14Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L23Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L12Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L22Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L311Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L312Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity R21Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity L21Entity =
        gz::sim::kNullEntity;
    gz::sim::Entity modelEntity =
        gz::sim::kNullEntity;
};

}

GZ_ADD_PLUGIN(
    gripper_plugins::SpringPlugin,
    gz::sim::System,
    gripper_plugins::SpringPlugin::ISystemConfigure,
    gripper_plugins::SpringPlugin::ISystemPreUpdate
)